#pragma once
#include <vector>
#include <tuple> 

enum class Piece {
	Empty = '-',
	Possible = '*',
	White = 'O',
	Black = 'X',
};

// an action consists of coordinates and the piece which will be placed there
typedef std::tuple<int, int, Piece> Action;

class OthelloBoard
{

private:
	Piece board[8][8];

public:
	OthelloBoard::OthelloBoard();

	// clears the board to the starting position
	void clearBoard();

	// prints the board state
	void printBoard();

	// sets the board to a given configuration
	void setBoard(const Piece val[][8]);

	// copies the board into a destination array
	void copyBoard(Piece dest[][8]);

	// gets all of the valid actions for the given player (either 'w' or 'b')
	std::vector<Action> getValidActions(const char &player);

	// flips pieces given a valid action
	void performAction(Action action);

	// gets the board state after applying the given action
	Piece** getNextBoardState(Action action);
};