#pragma once
#include <vector>
#include <tuple> 

enum class Piece {
	EMPTY = '-',
	POSSIBLE = '*',
	WHITE = 'O',
	BLACK = 'X',
};

// an action consists of coordinates and the piece which will be placed there
typedef std::tuple<int, int, Piece> Action;

class OthelloBoard
{

private:
	Piece board[8][8];

	void flipPieces(Action action);

	bool isActionValid(Action action);




public:
	OthelloBoard::OthelloBoard();

	void clearBoard();

	void printBoard();

	void setBoard(const Piece board[][8]);

	Piece** getBoard();


	// gets all of the valid actions for the given player (either 'w' or 'b')
	std::vector<Action> getValidActions(const char &player);

	// gets the board state after applying the given action
	Piece** getNextBoardState(Action action);
};