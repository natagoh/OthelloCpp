#include "GameView.h"
#include "SFML/Graphics/Shader.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <filesystem>
#include <iostream>


GameView::GameView() :
	_pieceBuffer(8.f),
	_pieceRadius(32.f),
	_boardSquareSize((_pieceRadius + _pieceBuffer) * 2),
	_boardSize(8 * _boardSquareSize) {}

const float GameView::getBoardSize() {
	return _boardSize;
}

const float GameView::getBoardSquareSize() {
	return _boardSquareSize;
}

void GameView::renderGameGrid(sf::RenderWindow& window) {
	/*
	* + -- +
	* | XX |
	* | XX |
	* + -- +
	*
	* There is going to be some buffer between the piece and the square containing it
	*/

	// create a render texture for the board
	sf::RenderTexture renderTexture;
	if (!renderTexture.create(_boardSize, _boardSize)) {
		printf("Error creating render texture\n");
	}

	// drawing uses the same functions
	renderTexture.clear();

	// draw board rectangle
	sf::RectangleShape boardRectangle(sf::Vector2f(_boardSize, _boardSize));
	sf::Color forestGreen = sf::Color(63, 90, 54);
	boardRectangle.setFillColor(forestGreen);
	renderTexture.draw(boardRectangle);
	renderTexture.display();

	for (int i = 1; i < 8; i++) {
		// draw horizontal board lines
		sf::Vertex horizontalLine[] = {
			sf::Vertex(sf::Vector2f(0.f, _boardSquareSize * i), sf::Color::Black),
			sf::Vertex(sf::Vector2f(_boardSize, _boardSquareSize * i), sf::Color::Black)
		};
		renderTexture.draw(horizontalLine, 2, sf::Lines);

		// draw vertical board lines
		sf::Vertex verticalLine[] = {
			sf::Vertex(sf::Vector2f(_boardSquareSize * i, 0.f), sf::Color::Black),
			sf::Vertex(sf::Vector2f(_boardSquareSize * i, _boardSize), sf::Color::Black)
		};
		renderTexture.draw(verticalLine, 2, sf::Lines);
	}

	// get the target texture (where the stuff has been drawn)
	const sf::Texture& boardTexture = renderTexture.getTexture();

	// draw game grid to the window
	sf::RectangleShape boardTextureRect(sf::Vector2f(_boardSize, _boardSize));
	boardTextureRect.setTexture(&boardTexture);
	//sf::Sprite boardSprite(boardTexture);
	window.draw(boardTextureRect);
}

void GameView::renderPiece(sf::RenderWindow& window, Piece color, int row, int col) {
	// draw a circle at position (row, col) on the board
	const float rowPos = _boardSquareSize / 2 + _boardSquareSize * row;
	const float colPos = _boardSquareSize / 2 + _boardSquareSize * col;

	// for ease of calculation, set origin to be at center of circle
	// black piece
	sf::CircleShape blackPiece(_pieceRadius);
	blackPiece.setOrigin(sf::Vector2f(_pieceRadius, _pieceRadius));
	blackPiece.setPosition(sf::Vector2f(colPos, rowPos));
	blackPiece.setFillColor(sf::Color::Black);

	// white piece
	sf::CircleShape whitePiece(_pieceRadius);
	whitePiece.setOrigin(sf::Vector2f(_pieceRadius, _pieceRadius));
	whitePiece.setPosition(sf::Vector2f(colPos, rowPos));
	whitePiece.setFillColor(sf::Color::White);
	whitePiece.setOutlineColor(sf::Color::Black);
	whitePiece.setOutlineThickness(1);

	// gray piece for possible moves
	sf::CircleShape possiblePiece(_pieceRadius);
	possiblePiece.setOrigin(sf::Vector2f(_pieceRadius, _pieceRadius));
	possiblePiece.setPosition(sf::Vector2f(colPos, rowPos));
	possiblePiece.setFillColor(sf::Color(0, 0, 0, 0.25 * 255));

	// bullseye for new pieces
	sf::CircleShape bullseye(4);
	bullseye.setOrigin(sf::Vector2f(4, 4));
	bullseye.setFillColor(sf::Color::Red);
	bullseye.setPosition(sf::Vector2f(colPos, rowPos));

	switch (color) {
	case Piece::Black:
		window.draw(blackPiece);
		break;

	case Piece::White:
		window.draw(whitePiece);
		break;

	case Piece::NewBlack:
		window.draw(blackPiece);

		// draw a red bullseye in the center
		window.draw(bullseye);
		break;

	case Piece::NewWhite:
		window.draw(whitePiece);

		// draw a red bullseye in the center
		window.draw(bullseye);
		break;

	case Piece::Possible:
		window.draw(possiblePiece);
		break;

	case Piece::Empty:
	default:
		break;

	}
}


void GameView::renderGameState(sf::RenderWindow& window, OthelloBoard& othello) {
	// render the game grid
	renderGameGrid(window);

	Piece board[8][8];
	othello.copyBoard(board);

	// render the pieces
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			renderPiece(window, board[row][col], row, col);
		}
	}

	window.display();
}


void GameView::renderGameOver(sf::RenderWindow& window, OthelloBoard& othello) {
	sf::Shader shader = sf::Shader{};
	 if (!sf::Shader::isAvailable() ) {
		std::cerr << "Shader not available\n";
		return; 
	 }
    if (!shader.loadFromFile("shaders/GaussianBlur.frag", sf::Shader::Fragment)) {
        std::cerr << "Couldn't load fragment shader\n";
		return;
    }
	shader.setUniform("u_xyBlurRadius", sf::Glsl::Vec2{ sf::Vector2f(0.05f, 0.05f) });


	// create a render texture for the board
	sf::RenderTexture renderTexture;
	if (!renderTexture.create(_boardSize, _boardSize)) {
		printf("Error creating render texture\n");
	}

	// drawing uses the same functions
	renderTexture.clear();

	// draw board rectangle
	const float gameOverScreenSize = 100.f;
	sf::RectangleShape boardRectangle(sf::Vector2f(gameOverScreenSize, gameOverScreenSize));
	const sf::Color semiTransparentGray = sf::Color(0, 0, 0, 0.25 * 255);
	boardRectangle.setFillColor(semiTransparentGray);
	renderTexture.draw(boardRectangle);
	renderTexture.display();

	// get the target texture (where the stuff has been drawn)
	const sf::Texture& boardTexture = renderTexture.getTexture();

	// draw game grid to the window
	sf::RectangleShape boardTextureRect(sf::Vector2f(_boardSize, _boardSize));
	boardTextureRect.setTexture(&boardTexture);
	//sf::Sprite boardSprite(boardTexture);
	window.draw(boardTextureRect, &shader);

	window.display();
}