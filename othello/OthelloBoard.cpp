#include "OthelloBoard.h"
#include<tuple> 
#include <cstring>

OthelloBoard::OthelloBoard() {
	this->clearBoard();
}

void OthelloBoard::clearBoard() {
	for (auto& arr : _board)
		std::fill(std::begin(arr), std::end(arr), Piece::Empty);
	_board[3][3] = Piece::White;
	_board[3][4] = Piece::Black;
	_board[4][3] = Piece::Black;
	_board[4][4] = Piece::White;

}

void OthelloBoard::printBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%c ", _board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void OthelloBoard::setBoard(const Piece val[][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_board[i][j] = val[i][j];
		}
	}
}

void OthelloBoard::copyBoard(Piece dest[][8]) {
	std::memcpy(dest, _board, 8 * 8 * sizeof(Piece));
}


bool inRange(int i, int j) {
	return (i < 0 || j < 0 || i >= 8 || j >= 8) ? false : true;
}

Piece getOppositeColor(Piece pieceColor) {
	return pieceColor == Piece::White ? Piece::Black : Piece::White;
}
std::vector<Action> OthelloBoard::getValidActions(const char &player) {
	const Piece pieceColor = player == 'O' ? Piece::White : Piece::Black;
	const Piece oppositeColor = getOppositeColor(pieceColor);

	std::vector<Action> actions;
	actions.reserve(8);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (_board[i][j] != pieceColor) {
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
					int rowOffset = i + k;
					int colOffset = j + l;
					bool moved = false;
					while (inRange(rowOffset, colOffset) && _board[rowOffset][colOffset] == oppositeColor) {
						rowOffset += k;
						colOffset += l;
						moved = true;
					}
					if (moved 
						&& inRange(rowOffset, colOffset) 
						&& _board[rowOffset][colOffset] != Piece::White 
						&& _board[rowOffset][colOffset] != Piece::Black) {
						actions.push_back(std::make_tuple(rowOffset, colOffset, pieceColor));
					}
				}
			}
		}
	}

	return actions;
}


void OthelloBoard::clearAllActionHints() {
	// clear all previous possible actions
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (_board[i][j] != Piece::White && _board[i][j] != Piece::Black) {
				_board[i][j] = Piece::Empty;
			}
		}
	}
}

void OthelloBoard::enableActionHints(std::vector<Action> &actions) {
	clearAllActionHints();

	// display possible actions
	for (const auto& action : actions) {
		const auto [row, col, _] = action;
		_board[row][col] = Piece::Possible;
	}

}

void OthelloBoard::performAction(Action action) {
	const auto [row, col, pieceColor] = action;
	const Piece oppositeColor = getOppositeColor(pieceColor);

	clearAllActionHints();

	bool flip[8][8];
	for (auto& arr : flip) {
		std::fill(std::begin(arr), std::end(arr), false);
	}

	// place the piece at (row, col) on the board
	flip[row][col] = true;

	// search all eight directions for opposite color pieces
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) {
				continue;
			}

			// search direction for possible pieces to flip
			// keep searching in the given i, j offset direction
			int rowOffset = row + i;
			int colOffset = col + j;
			while (inRange(rowOffset, colOffset) && _board[rowOffset][colOffset] == oppositeColor) {
				rowOffset += i;
				colOffset += j;
			}

			// found matching end piece, so we can flip
			if (_board[rowOffset][colOffset] == pieceColor) {
				do {
					rowOffset -= i;
					colOffset -= j;
					flip[rowOffset][colOffset] = true;
				} while (rowOffset != row && colOffset != col);
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (flip[i][j]) {
				_board[i][j] = pieceColor;
			}
		}
	}
}

bool OthelloBoard::isGameOver() {
	// check that the board is all filled
	int countEmpty = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (_board[i][j] == Piece::Empty) {
				countEmpty++;
			}
		}
	}
	if (countEmpty == 64) {
		return true;
	}

	// check that both players have no more possible moves
	const char players[2] = { (char)Piece::Black, (char)Piece::White };
	for (const auto& player : players) {
		const auto actions = getValidActions(player);
		if (!actions.empty()) {
			return false;
		}
	}

	return true;
}