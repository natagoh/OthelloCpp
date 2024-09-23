#pragma once

#include "PlayerInterface.h"
#include <vector>

// Player interface
class MinimaxPlayer : public PlayerInterface {

private:
	Piece _color;

public:
	// initializes a player with the given color
	MinimaxPlayer(const Piece& color);
	~MinimaxPlayer();

	// gets the action to perform at the current game state
	std::optional<Action> getNextAction(OthelloBoard& othello);

	Piece getColor();
};