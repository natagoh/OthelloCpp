#include "OthelloBoard.h"
#include<tuple> 
#include <cstring>

OthelloBoard::OthelloBoard() {
	this->clearBoard();
}

void OthelloBoard::clearBoard() {
	for (auto& arr : board)
		std::fill(std::begin(arr), std::end(arr), Piece::EMPTY);
	board[3][3] = Piece::WHITE;
	board[3][4] = Piece::BLACK;
	board[4][3] = Piece::BLACK;
	board[4][4] = Piece::WHITE;

}

void OthelloBoard::printBoard() {
	for (int i = 0; i < std::size(board); i++) {
		for (int j = 0; j < std::size(board[0]); j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void OthelloBoard::setBoard(const Piece val[][8]) {
	for (int i = 0; i < std::size(board); i++) {
		for (int j = 0; j < std::size(board[0]); j++) {
			board[i][j] = val[i][j];
		}
	}
}

void OthelloBoard::copyBoard(Piece dest[][8]) {
	std::memcpy(dest, board, 8 * 8 * sizeof(Piece));
}


bool inRange(int i, int j) {
	return (i < 0 || j < 0 || i >= 8 || j >= 8) ? false : true;
}

Piece getOppositeColor(Piece pieceColor) {
	return pieceColor == Piece::WHITE ? Piece::BLACK : Piece::WHITE;
}
std::vector<Action> OthelloBoard::getValidActions(const char &player) {
	const Piece pieceColor = player == 'O' ? Piece::WHITE : Piece::BLACK;
	const Piece oppositeColor = getOppositeColor(pieceColor);

	std::vector<Action> actions;
	actions.reserve(8);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != pieceColor) {
				continue;
			}

			// search for opposite color piece in all 8 directions, diagonals
			for (int k = -1; k <= 1; k++) {
				for (int l = -1; l <= 1; l++) {
					if (k == 0 && l == 0) {
						continue;
					}

					// search direction for action
					// keep searching in the given i, j offset direction
					int iOffset = i + k;
					int jOffset = j + l;
					bool moved = false;
					while (inRange(iOffset, jOffset) && board[iOffset][jOffset] == oppositeColor) {
						iOffset += k;
						jOffset += l;
						moved = true;
					}
					if (moved && inRange(iOffset, jOffset) && board[iOffset][jOffset] == Piece::EMPTY) {
						actions.push_back(std::make_tuple(iOffset, jOffset, pieceColor));
					}
				}
			}
		}
	}

	return actions;
}

void OthelloBoard::performAction(Action action) {
	const int x = std::get<0>(action);
	const int y = std::get<1>(action);
	const Piece pieceColor = std::get<2>(action);
	const Piece oppositeColor = getOppositeColor(pieceColor);

	bool flip[8][8];
	for (auto& arr : flip)
		std::fill(std::begin(arr), std::end(arr), false);

	// place the piece at (x, y) on the board
	flip[x][y] = true;

	// search all eight directions for opposite color pieces
	for (int k = -1; k <= 1; k++) {
		for (int l = -1; l <= 1; l++) {
			if (k == 0 && l == 0) {
				continue;
			}

			// search direction for possible pieces to flip
			// keep searching in the given i, j offset direction
			int iOffset = x + k;
			int jOffset = y + l;
			while (inRange(iOffset, jOffset) && board[iOffset][jOffset] == oppositeColor) {
				iOffset += k;
				jOffset += l;
			}

			// found matching end piece, so we can flip
			if (board[iOffset][jOffset] == pieceColor) {
				do {
					iOffset -= k;
					jOffset -= l;
					flip[iOffset][jOffset] = true;
				} while (iOffset != x && jOffset != y);
			}
		}
	}
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (flip[i][j]) {
				board[i][j] = pieceColor;
			}
		}
	}
	
	
}