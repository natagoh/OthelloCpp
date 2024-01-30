#pragma once
#include <vector>
#include <tuple> 

enum class Piece {
	Empty = '-',
	Possible = '*',
	White = 'O',
	Black = 'X',
	NewBlack = 'b',
	NewWhite = 'w',
};

// an action consists of coordinates and the piece which will be placed there
typedef std::tuple<int, int, Piece> Action;

class OthelloBoard
{

private:
	Piece _board[8][8];

public:
	OthelloBoard();

	// clears the board to the starting position
	void clearBoard();

	// clears all special pieces: action hints, new piece indicators
	// option to keep recent moves
	void clearSpecialPieces(const bool keepRecentMove = false);

	// prints the board state
	void printBoard();

	// sets the board to a given configuration
	void setBoard(const Piece val[][8]);

	// copies the board into a destination array
	void copyBoard(Piece dest[][8]);

	// gets all of the valid actions for the given player (either 'w' or 'b')
	std::vector<Action> getValidActions(const char &player);

	// show action hints on the board
	void enableActionHints(const std::vector<Action> &actions);

	// flips pieces given a valid action
	void performAction(const Action &action);

	// checks if the game is over (no more possible actions for either player)
	bool isGameOver();

};