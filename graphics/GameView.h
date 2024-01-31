#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "../othello/OthelloBoard.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

class GameView {
private:
	const float _pieceBuffer;
	const float _pieceRadius;
	const float _boardSquareSize;
	const float _boardSize;

	void drawGameGrid(sf::RenderTarget &renderTarget);
	void drawPiece(sf::RenderTarget &renderTarget, const Piece &color, const int row, const int col);
	void drawGameState(sf::RenderTarget &renderTarget, OthelloBoard& othello);

public:
	GameView();

	// renders the current game state to the window
	void renderGameState(sf::RenderWindow& window, OthelloBoard& othello);

	// renders the game over screen
	void renderGameOver(sf::RenderWindow& window, OthelloBoard& othello);
	
	const float getBoardSquareSize();
	const float getBoardSize();
};