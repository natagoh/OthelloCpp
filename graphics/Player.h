#pragma once
#include "../othello/OthelloBoard.h"

class Player {
private:
	Piece color;

public:
	// gets the action to perform at the current game state
	virtual Action getNextAction(Othello othello);

	Piece getColor() {
		return color;
	}

};