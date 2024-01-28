#include "OthelloBoard.h"
#include<tuple> 

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

void OthelloBoard::flipPieces(Action action) {

}

bool OthelloBoard::isActionValid(Action action) {
	return true;
}

bool inRange(int i, int j) {
	return (i < 0 || j < 0 || i >= 8 || j >= 8) ? false : true;
}

std::vector<Action> OthelloBoard::getValidActions(const char &player) {
	const Piece pieceColor = player == 'O' ? Piece::WHITE : Piece::BLACK;
	const Piece opposingColor = pieceColor == Piece::WHITE ? Piece::BLACK : Piece::WHITE;

	printf("opposingColor: %c\n", opposingColor);
	std::vector<Action> actions;
	actions.reserve(8);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != pieceColor) {
				continue;
			}

			printf("i: %i, j: %i\n", i, j);
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
					while (inRange(iOffset, jOffset) && board[iOffset][jOffset] == opposingColor) {
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

	// show actions on the board
	for (const auto& action : actions) {
		const int i = std::get<0>(action);
		const int j = std::get<1>(action);
		const Piece piece = std::get<2>(action);
		board[i][j] = Piece::POSSIBLE;
	}

	return actions;
}