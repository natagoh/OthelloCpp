#pragma once

#include "../othello/OthelloBoard.h"
#include "GameView.h"

#include <optional>
#include <SFML/Graphics.hpp>

struct Player {
	Piece color;

	Player(Piece color) : color(color) {}
};


enum class GameStepOutcome {
	Complete,	// player finished their turn, supplied an action
	Incomplete,	// still waiting for player to finish their turn and supply an action
};
class GameManager {
private:
	// black goes first
	Player _players[2] = {Player(Piece::Black), Player(Piece::White)};
	OthelloBoard _othello;
	sf::RenderWindow _window;
	GameView _gameView;
	sf::Clock _clock;
	sf::Clock _gameClock;

	// gets action for human turn out of possible actions provided
	std::optional<Action> GameManager::getHumanAction(std::vector<Action> actions);

	GameStepOutcome processGameStep(const Player& player, bool isHuman = false);


public:
	GameManager::GameManager(OthelloBoard &othello);

	void processGameLoop();

};