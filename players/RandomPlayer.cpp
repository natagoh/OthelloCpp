#include "RandomPlayer.h"


RandomPlayer::RandomPlayer(const Piece& color) : _color(color) {}

RandomPlayer::~RandomPlayer() {}

Piece RandomPlayer::getColor() {
	return _color;
}


// returns random action
std::optional<Action> RandomPlayer::getNextAction(OthelloBoard& othello) {

	return std::nullopt;
	/*
	const auto actions = othello.getValidActions((char)_color);

   if (actions.empty()) {
	   return std::nullopt;
   }

   // pick a random action
   int idx = rand() % actions.size();
   const auto action = actions[idx];
   return action;
   */

}