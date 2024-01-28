// OthelloCpp.cpp : Defines the entry point for the application.
//

#include "OthelloCpp.h"
#include "OthelloBoard.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	OthelloBoard othello = OthelloBoard();

	othello.printBoard();

	const auto actions = othello.getValidActions('X');

	printf("possible values for player X\n");
	Piece board[8][8];
	Piece originalBoard[8][8];
	othello.copyBoard(board);
	othello.copyBoard(originalBoard);

	// show actions on the board
	for (const auto& action : actions) {
		const int i = std::get<0>(action);
		const int j = std::get<1>(action);
		const Piece piece = std::get<2>(action);
		board[i][j] = Piece::POSSIBLE;
	}

	othello.setBoard(board);
	othello.printBoard();


	// performing action(3, 2, BLACK)
	printf("after performing action (3, 2, BLACK)\n");
	othello.setBoard(originalBoard);
	othello.performAction(std::make_tuple(3, 2, Piece::BLACK));
	othello.printBoard();

	return 0;
}
