﻿// OthelloCpp.cpp : Defines the entry point for the application.
//

#include "OthelloCpp.h"
#include "OthelloBoard.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	OthelloBoard othello = OthelloBoard();

	othello.printBoard();

	auto actions = othello.getValidActions('X');

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
		board[i][j] = Piece::Possible;
	}

	othello.setBoard(board);
	othello.printBoard();


	// performing action(3, 2, BLACK)
	printf("after performing action (3, 2, BLACK)\n");
	othello.setBoard(originalBoard);
	othello.performAction(std::make_tuple(3, 2, Piece::Black));
	othello.printBoard();

	// now try O actions
	actions = othello.getValidActions('O');

	printf("possible values for player O\n");
	othello.copyBoard(board);
	othello.copyBoard(originalBoard);

	// show actions on the board
	for (const auto& action : actions) {
		const int i = std::get<0>(action);
		const int j = std::get<1>(action);
		const Piece piece = std::get<2>(action);
		board[i][j] = Piece::Possible;
	}
	othello.setBoard(board);
	othello.printBoard();

	// performing action(4, 2, WHITE)
	othello.setBoard(originalBoard);
	printf("before move\n");
	othello.printBoard();
	printf("after performing action\n");
	othello.performAction(std::make_tuple(2, 2, Piece::White));
	othello.printBoard();


	// game loop
	printf("========GAME LOOP=======\n");
	othello.clearBoard();
	for (int i = 0; i < 3; i++) {
		// player X turn
		printf("player X turn\n");
		auto actions = othello.getValidActions((char) Piece::Black);
		
		// pick a random action
		int idx = rand() % actions.size();
		Action action = actions[idx];

		othello.performAction(action);
		othello.printBoard();

		// player O turn
		printf("player O turn\n");
		actions = othello.getValidActions((char) Piece::White);

		// pick a random action
		idx = rand() % actions.size();
		action = actions[idx];

		othello.performAction(action);
		othello.printBoard();
	}

	return 0;
}
