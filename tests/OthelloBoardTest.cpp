#include <gtest/gtest.h>
#include "../othello/OthelloBoard.h"


TEST(OthelloBoardTest, TestClearSpecialPieces) {
	const Piece board[8][8] = {
		{Piece::Possible, Piece::NewBlack, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::NewWhite, Piece::White, Piece::White, Piece::White, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::White, Piece::Black, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::White, Piece::Black, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::White, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
	};

	const Piece expectedBoard[8][8] = {
		{Piece::Empty, Piece::Black, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::White, Piece::White, Piece::White, Piece::White, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::White, Piece::Black, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::White, Piece::Black, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::White, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
	};

	OthelloBoard othello = OthelloBoard();
	othello.setBoard(board);
	othello.clearSpecialPieces();

	Piece boardAfter[8][8];
	othello.copyBoard(boardAfter);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			EXPECT_EQ(boardAfter[i][j], expectedBoard[i][j]);
		}
	}
}


// tests that pieces are getting placed properly
TEST(OthelloBoardTest, TestPerformAction) {
	/**
	 * The case performAction is struggling with:
	 *
	 *	- - - - - - - -
	 *	- - - X - - - -
	 *	- - * X X O - -
	 *	- - - X O X - -
	 *	- - - - X O X -
	 *	- - - - - - O -
	 *	- - - - - - - -
	 *
	 *	- - - - - - - -
	 *	- - - - - - - -
	 *	- - - X - - - -
	 *	- - O X O O - -
	 *	- - - X O X - -
	 *	- - - - X O X -
	 *	- - - - - - O -
	 *	- - - - - - - -
	 *
	**/
	const Piece board[8][8] = {
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::Black, Piece::White, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::White, Piece::Black, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::White, Piece::Black, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::White, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
	};

	const Action action = std::make_tuple(3, 2, Piece::White);

	const Piece expectedBoard[8][8] = {
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::NewWhite, Piece::White, Piece::White, Piece::White, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::White, Piece::Black, Piece::Empty, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Black, Piece::White, Piece::Black, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::White, Piece::Empty},
		{Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty, Piece::Empty},
	};

	OthelloBoard othello = OthelloBoard();
	othello.setBoard(board);
	othello.performAction(action);

	Piece boardAfterAction[8][8];
	othello.copyBoard(boardAfterAction);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			EXPECT_EQ(boardAfterAction[i][j], expectedBoard[i][j]);
		}
	}
}
