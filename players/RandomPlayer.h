#pragma once

#include "PlayerInterface.h"
#include<vector>

// Player interface
class RandomPlayer : public PlayerInterface {

private:
	Piece _color;

public:
	// initializes a player with the given color
	RandomPlayer(const Piece& color);
	~RandomPlayer() override;

	// gets the action to perform at the current game state
	std::optional<Action> getNextAction(OthelloBoard &othello);

	Piece getColor();
};