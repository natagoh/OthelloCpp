#include "MinimaxPlayer.h"


namespace {
	std::vector<std::vector<float>> boardWeights{
		{1.01, -0.43, 0.38, 0.07, 0.00, 0.42, -0.20, 1.02},
		{-0.27, -0.74, -0.16, -0.14, -0.13, -0.25, -0.65, -0.39},
		{0.56, -0.30, 0.12, 0.05, -0.04, 0.07, -0.15, 0.48},
		{0.01, -0.08, 0.01, -0.01, -0.04, -0.02, -0.12, 0.03},
		{-0.10, -0.08, 0.01, -0.01, -0.03, 0.02, -0.04, -0.20},
		{0.59, -0.23, 0.06, 0.01, 0.04, 0.06, -0.19, 0.35},
		{-0.06, -0.55, -0.18, -0.08, -0.15, -0.31, -0.82, -0.58},
		{0.96, -0.42, 0.67, -0.02, -0.03, 0.81, -0.51, 1.01}
	};

	// evaluate the board state based on the color 
	float evaluateBoard(const Piece (&board)[8][8], const Piece& color) {
		float score = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j] != color) {
					continue;
				}
				score += boardWeights[i][j];
			}
		}
		return score;
	}

	float evaluateAction(OthelloBoard& othello, const Action& action, const Piece& color) {
		// save initial board state
		Piece board[8][8];
		othello.copyBoard(board);

		// get board state after action
		othello.performAction(action);

		Piece newBoard[8][8];
		othello.copyBoard(newBoard);

		// reset board state to before action
		othello.setBoard(board);

		return evaluateBoard(newBoard, color);
	}

} // namespace

MinimaxPlayer::MinimaxPlayer(const Piece& color) : _color(color) {}

MinimaxPlayer::~MinimaxPlayer() {}

Piece MinimaxPlayer::getColor() {
	return _color;
}

// returns minimax action
std::optional<Action> MinimaxPlayer::getNextAction(OthelloBoard& othello) {
	Piece board[8][8];
	othello.copyBoard(board);

	const auto currentPlayer = _color;
	const auto actions = othello.getValidActions((char)currentPlayer);

	if (actions.empty()) {
		return std::nullopt;
	}

	// pick action with highest heuristic score
	float highestScore = 0;
	Action bestAction = actions[0];
	for (const auto action : actions) {
		float score = evaluateAction(othello, action, currentPlayer);
		if (score > highestScore) {
			bestAction = action;
		}
	}
	return bestAction;
}