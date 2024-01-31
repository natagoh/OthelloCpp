#pragma once

#include <optional>
#include "../othello/OthelloBoard.h"

// Player interface
class PlayerInterface {
public:
	// initializes a player with the given color
	virtual ~PlayerInterface() = default;

	// gets the action to perform at the current game state
	virtual std::optional<Action> getNextAction(OthelloBoard &othello) = 0;
	virtual Piece getColor() = 0;
};