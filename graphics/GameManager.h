#pragma once

#include "../othello/OthelloBoard.h"
#include "GameView.h"

#include <optional>
#include <SFML/Graphics.hpp>

struct Player {
	Piece color;

	Player(Piece color) : color(color) {}
};

class GameManager {
private:
	// black goes first
	Player _players[2] = {Player(Piece::Black), Player(Piece::White)};
	OthelloBoard _othello;
	sf::RenderWindow _window;
	GameView _gameView;

	// gets action for human turn out of possible actions provided
	std::optional<Action> GameManager::getHumanAction(std::vector<Action> actions);

public:
	GameManager::GameManager(OthelloBoard &othello);

	void processGameStep(const Player &player, bool isHuman = false);

	void processGameLoop();

};