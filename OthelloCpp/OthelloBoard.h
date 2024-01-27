#pragma once
#include <vector>

enum class State {
	EMPTY = '*',
	WHITE = 'w',
	BLACK = 'b',
};

class OthelloBoard
{

private:
	State board[8][8];
	// std::vector<std::vector<State>> board;

public:
	OthelloBoard::OthelloBoard();

	void clearBoard();

	void printBoard();
};