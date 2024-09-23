#include "MinimaxPlayer.h"
#include <limits>

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

	// TODO: consolidate with Othello Piece utilities
	Piece getOppositeColor(const Piece& pieceColor) {
		return pieceColor == Piece::White ? Piece::Black : Piece::White;
	}

	// Opponent turn: find the action that minimizes the board heuristic score
	float minimize(OthelloBoard& othello, const Piece& color) {
		Piece initialBoard[8][8];
		othello.copyBoard(initialBoard);

		// find the action that minimizes the board heuristic state
		float minScore = std::numeric_limits<float>::max();
		const auto oppositeColor = getOppositeColor(color);
		const auto actions = othello.getValidActions((char)oppositeColor);
		for (const auto action : actions) {
			othello.performAction(action);

			float score = evaluateAction(othello, action, oppositeColor);
			minScore = std::min(score, minScore);

			// reset othello board state to before action was performed
			othello.setBoard(initialBoard);
		}
		return minScore;
	}


	// Player turn: find the action that maximizes the board heuristic score
	std::optional<Action> maximize(OthelloBoard& othello, const Piece& color) {
		Piece initialBoard[8][8];
		othello.copyBoard(initialBoard);

		float maxScore = std::numeric_limits<float>::min();
		const auto actions = othello.getValidActions((char)color);
		if (actions.empty()) {
			return std::nullopt;
		}

		auto bestAction = actions[0];
		for (const auto action : actions) {
			// othello board state after performing action
			othello.performAction(action);

			float minimizerScore = minimize(othello, color);
			if (minimizerScore > maxScore) {
				maxScore = minimizerScore;
				bestAction = action;
			}

			// reset othello board state to before action was performed
			othello.setBoard(initialBoard);
		}
		return bestAction;
	}


	// 2 ply minimax
	std::optional<Action> minimax(OthelloBoard& othello, const Piece& color, const int ply) {
		return maximize(othello, color);
	}


} // namespace

MinimaxPlayer::MinimaxPlayer(const Piece& color, const int ply) : _color(color), _ply(ply) {}

MinimaxPlayer::~MinimaxPlayer() {}

Piece MinimaxPlayer::getColor() {
	return _color;
}

// returns minimax action
std::optional<Action> MinimaxPlayer::getNextAction(OthelloBoard& othello) {
	if (_ply == 2) {
		return minimax(othello, _color, 2);
	}
	
	// 1 ply minimax
	Piece board[8][8];
	othello.copyBoard(board);

	const auto currentPlayer = _color;
	const auto actions = othello.getValidActions((char)currentPlayer);

	if (actions.empty()) {
		return std::nullopt;
	}

	// 1ply minimax: pick action with highest heuristic score
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