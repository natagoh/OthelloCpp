#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "../othello/OthelloBoard.h"

class GameView {
private:
	const float _pieceBuffer;
	const float _pieceRadius;
	const float _boardSquareSize;
	const float _boardSize;

	void renderGameGrid(sf::RenderWindow& window);
	void renderPiece(sf::RenderWindow& window, Piece color, int row, int col);

public:
	GameView();

	// renders the current game state to the window
	void renderGameState(sf::RenderWindow& window, OthelloBoard& othello);

	const float getBoardSquareSize();
	const float getBoardSize();
};