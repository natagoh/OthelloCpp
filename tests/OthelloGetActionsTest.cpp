#include <gtest/gtest.h>
#include "../othello/OthelloBoard.h"


/*
player X turn

   0 1 2 3 4 5 6 7
 0 - w X * * * - -
 1 - - O O O * - -
 2 X - X O O * * -
 3 X X X X O O * *
 4 X X X O O * O -
 5 X O X O O O * *
 6 X O O O O O * -
 7 X X X X X * * -

*/
TEST(OthelloGetActionsTest, TestGetAllPossibleActions) {
	const Piece board[8][8] = {
		{ Piece::Empty, Piece::NewWhite, Piece::Black, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
	};

	const Piece expectedBoard[8][8] = {
		{ Piece::Possible, Piece::White, Piece::Black, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
		{ Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty },
	};

	OthelloBoard othello = OthelloBoard();
	othello.setBoard(board);
	const auto actions = othello.getValidActions((char)Piece::Black);
	othello.enableActionHints(actions);
	othello.printBoard();

	Piece boardAfterAction[8][8];
	othello.copyBoard(boardAfterAction);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			EXPECT_EQ(boardAfterAction[i][j], expectedBoard[i][j]);
		}
	}

}

