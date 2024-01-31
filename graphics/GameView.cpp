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
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>


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
	// std::cout << std::filesystem::current_path() << std::endl;

	// initialize shader
	sf::Shader shader = sf::Shader{};
	if (!sf::Shader::isAvailable()) {
		std::cerr << "Shader not available\n";
		return;
	}
	/*
   if (!shader.loadFromFile("shaders/GaussianBlur.frag", sf::Shader::Fragment)) {
	   std::cerr << "Couldn't load fragment shader\n";
	   return;
   }
   shader.setUniform("blurOffset", sf::Glsl::Vec2{ sf::Vector2f(5.f, 10.f) });
   shader.setUniform("texture", sf::Shader::CurrentTexture);
   */

   //
	if (!shader.loadFromFile("shaders/Blur.frag", sf::Shader::Fragment)) {
		std::cerr << "Couldn't load fragment shader\n";
		return;
	}
	shader.setUniform("blurSize", 1);
	shader.setUniform("texture", sf::Shader::CurrentTexture);

	// shader settings
	sf::BlendMode blendPremultiplied = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha);

	sf::RenderStates statesBlur;
	statesBlur.blendMode = blendPremultiplied;
	statesBlur.shader = &shader;

	sf::RenderStates statesPremultiplied;
	statesPremultiplied.blendMode = blendPremultiplied;


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
	window.draw(windowSprite, statesBlur);


	// draw score count window
	const int winnerTextSize = 36;
	const int textSize = 24;

	const float menuSize = _boardSize * 0.6;
	const float menuVerticalPadding = winnerTextSize;
	const float textPadding = textSize;

	const float menuHeight = 
		winnerTextSize + 2 * textSize	// height of text
		+ menuVerticalPadding * 2		// vertical padding
		+ textPadding * 2;				// text padding


	sf::RectangleShape menuRectangle(sf::Vector2f(menuSize, menuHeight));
	menuRectangle.setPosition(sf::Vector2f(
		_boardSize / 2 - menuSize / 2, 
		_boardSize / 2 - menuHeight / 2
	));
	menuRectangle.setFillColor(sf::Color(0, 0, 0, 0.8 * 255));
	window.draw(menuRectangle);


	// fonts
	sf::Font font;
	if (!font.loadFromFile("shaders/RobotoMono-Regular.ttf")) {
		printf("[Error] unable to load font from file\n");
	}

	sf::Text winnerText;
	winnerText.setFont(font); // font is a sf::Font
	winnerText.setCharacterSize(winnerTextSize); // in pixels, not points!
	winnerText.setFillColor(sf::Color::White);
	winnerText.setStyle(sf::Text::Bold | sf::Text::Underlined);

	// draw winner text
	const auto& [blackScore, whiteScore] = othello.getScore();
	std::string winnerStr = "";
	if (blackScore == whiteScore) {
		winnerStr = "Tie!";
	}
	else if (blackScore > whiteScore) {
		winnerStr = "Black wins!";
	}
	else {
		winnerStr = "White wins!";
	}
	winnerText.setString(winnerStr);

	const  sf::FloatRect winnerTextBounds = winnerText.getLocalBounds();
	const sf::Vector2f menuRectangleSize(menuRectangle.getSize());
	winnerText.setPosition(sf::Vector2f(
		menuRectangle.getPosition().x + (menuRectangleSize.x - winnerTextBounds.width) / 2,
		menuRectangle.getPosition().y + menuVerticalPadding
	));
	window.draw(winnerText);

	// draw white piece score
	sf::Text whiteText;
	whiteText.setFont(font); // font is a sf::Font
	whiteText.setCharacterSize(textSize); // in pixels, not points!
	whiteText.setFillColor(sf::Color::White);
	whiteText.setStyle(sf::Text::Bold);
	whiteText.setString("(white) x " + std::to_string(whiteScore));

	const  sf::FloatRect whiteTextBounds = whiteText.getLocalBounds();
	whiteText.setPosition(sf::Vector2f(
		menuRectangle.getPosition().x + (menuRectangleSize.x - whiteTextBounds.width) / 2,
		winnerText.getPosition().y + winnerTextSize + textPadding
	));
	window.draw(whiteText);

	// draw black piece score
	sf::Text blackText;
	blackText.setFont(font); // font is a sf::Font
	blackText.setCharacterSize(textSize); // in pixels, not points!
	blackText.setFillColor(sf::Color::White);
	blackText.setStyle(sf::Text::Bold);

	blackText.setString("(black) x " + std::to_string(blackScore));
	const  sf::FloatRect blackTextBounds = whiteText.getLocalBounds();
	blackText.setPosition(sf::Vector2f(
		menuRectangle.getPosition().x + (menuRectangleSize.x - blackTextBounds.width) / 2,
		whiteText.getPosition().y + textSize + textPadding
	));
	window.draw(blackText);
	window.display();
}

void GameView::drawGameGrid(sf::RenderTarget& renderTarget) {
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

void GameView::drawPiece(sf::RenderTarget& renderTarget, const Piece& color, const int row, const int col) {
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

void GameView::drawGameState(sf::RenderTarget& renderTarget, OthelloBoard& othello) {
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