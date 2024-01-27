#include "OthelloBoard.h"


OthelloBoard::OthelloBoard() {
	this->clearBoard();
}

void OthelloBoard::clearBoard() {
	for (auto& arr : board)
		std::fill(std::begin(arr), std::end(arr), State::EMPTY);
	board[3][3] = State::WHITE;
	board[4][3] = State::BLACK;
	board[3][4] = State::BLACK;
	board[4][4] = State::WHITE;

}

void OthelloBoard::printBoard() {
	for (int i = 0; i < std::size(board); i++) {
		for (int j = 0; j < std::size(board[0]); j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}