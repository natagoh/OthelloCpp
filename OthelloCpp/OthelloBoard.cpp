#include "OthelloBoard.h"


OthelloBoard::OthelloBoard() {
	this->clearBoard();
}

void OthelloBoard::clearBoard() {
	for (auto& arr : board)
		std::fill(std::begin(arr), std::end(arr), Piece::EMPTY);
	board[3][3] = Piece::WHITE;
	board[4][3] = Piece::BLACK;
	board[3][4] = Piece::BLACK;
	board[4][4] = Piece::WHITE;

}

void OthelloBoard::printBoard() {
	for (int i = 0; i < std::size(board); i++) {
		for (int j = 0; j < std::size(board[0]); j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}