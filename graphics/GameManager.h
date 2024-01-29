#pragma once

#include "../othello/OthelloBoard.h"

struct Player {
	Piece color;

	Player(Piece color) : color(color) {}
};

class GameManager {
private:
	// black goes first
	Player _players[2] = {Player(Piece::Black), Player(Piece::White)};
	OthelloBoard _othello;


public:
	GameManager::GameManager(OthelloBoard &othello);

	void processGameStep(const Player &player);

	void processGameLoop();

};