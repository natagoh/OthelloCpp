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
	GameView::GameView();

	void renderGameState(sf::RenderWindow& window, Piece board[8][8]);
};