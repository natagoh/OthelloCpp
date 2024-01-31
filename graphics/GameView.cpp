#include "GameView.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
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

void GameView::renderGameState(sf::RenderWindow& window, OthelloBoard& othello) {
	// draw game state to render texture
	sf::RenderTexture renderTexture;
	if (!renderTexture.create(_boardSize, _boardSize)) {
		printf("Error creating render texture\n");
	}
	drawGameState(renderTexture, othello);

	// draw render texture to window
	renderTexture.display();
	const sf::Texture& windowTexture = renderTexture.getTexture();
	sf::Sprite windowSprite(windowTexture);
	window.draw(windowSprite);
	window.display();
}


void GameView::renderGameOver(sf::RenderWindow& window, OthelloBoard& othello) {
	std::cout << std::filesystem::current_path() << std::endl;

	// initialize shader
	sf::Shader shader = sf::Shader{};
	 if (!sf::Shader::isAvailable() ) {
		std::cerr << "Shader not available\n";
		return; 
	 }
    if (!shader.loadFromFile("graphics/shaders/GaussianBlur.frag", sf::Shader::Fragment)) {
        std::cerr << "Couldn't load fragment shader\n";
		return;
    }
	shader.setUniform("blurOffset", sf::Glsl::Vec2{ sf::Vector2f(10.f, 10.f) });
	shader.setUniform("texture", sf::Shader::CurrentTexture);

	// draw game state to render texture
	sf::RenderTexture renderTexture;
	if (!renderTexture.create(_boardSize, _boardSize)) {
		printf("Error creating render texture\n");
	}
	drawGameState(renderTexture, othello);

	// draw render texture to window
	renderTexture.display();
	const sf::Texture& windowTexture = renderTexture.getTexture();
	sf::Sprite windowSprite(windowTexture);
	window.draw(windowSprite);
	window.display();
}

void GameView::drawGameGrid(sf::RenderTarget &renderTarget) {
	renderTarget.clear();

	// draw board rectangle
	sf::RectangleShape boardRectangle(sf::Vector2f(_boardSize, _boardSize));
	sf::Color forestGreen = sf::Color(63, 90, 54);
	boardRectangle.setFillColor(forestGreen);
	renderTarget.draw(boardRectangle);

	for (int i = 1; i < 8; i++) {
		// draw horizontal board lines
		sf::Vertex horizontalLine[] = {
			sf::Vertex(sf::Vector2f(0.f, _boardSquareSize * i), sf::Color::Black),
			sf::Vertex(sf::Vector2f(_boardSize, _boardSquareSize * i), sf::Color::Black)
		};
		renderTarget.draw(horizontalLine, 2, sf::Lines);

		// draw vertical board lines
		sf::Vertex verticalLine[] = {
			sf::Vertex(sf::Vector2f(_boardSquareSize * i, 0.f), sf::Color::Black),
			sf::Vertex(sf::Vector2f(_boardSquareSize * i, _boardSize), sf::Color::Black)
		};
		renderTarget.draw(verticalLine, 2, sf::Lines);
	}
}

void GameView::drawPiece(sf::RenderTarget &renderTarget, const Piece &color, const int row, const int col) {
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
		renderTarget.draw(blackPiece);
		break;

	case Piece::White:
		renderTarget.draw(whitePiece);
		break;

	case Piece::NewBlack:
		renderTarget.draw(blackPiece);

		// draw a red bullseye in the center
		renderTarget.draw(bullseye);
		break;

	case Piece::NewWhite:
		renderTarget.draw(whitePiece);

		// draw a red bullseye in the center
		renderTarget.draw(bullseye);
		break;

	case Piece::Possible:
		renderTarget.draw(possiblePiece);
		break;

	case Piece::Empty:
	default:
		break;

	}
}

void GameView::drawGameState(sf::RenderTarget &renderTarget, OthelloBoard& othello) {
	// render the game grid
	drawGameGrid(renderTarget);

	Piece board[8][8];
	othello.copyBoard(board);

	// render the pieces
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			drawPiece(renderTarget, board[row][col], row, col);
		}
	}
}