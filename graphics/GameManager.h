#pragma once

#include "../othello/OthelloBoard.h"
#include "GameView.h"
#include "../players/PlayerInterface.h"

#include <optional>
#include <SFML/Graphics.hpp>

/*
struct Player {
	Piece color;

	Player(Piece color) : color(color) {}
};
*/

enum class GameStepOutcome {
	Action,		// player finished their turn, supplied an action
	Pending,	// still waiting for player to finish their turn and supply an action
};


class GameManager {
private:
	// black goes first
	OthelloBoard _othello;
	sf::RenderWindow _window;
	GameView _gameView;
	sf::Clock _clock;
	bool _useOpponentDelay;

	// gets action for human turn out of possible actions provided
	const std::optional<Action> getHumanAction(
		std::vector<Action> actions, 
		std::optional<sf::Vector2i> mousePos
	);
	const std::optional<sf::Vector2i> getMouseClickPos();

	GameStepOutcome gameStep(
		std::shared_ptr<PlayerInterface> player,
		bool isHuman = false, 
		const std::optional<sf::Vector2i> &mousePos = std::nullopt
	);
	
	void pollWindowEvent();

public:
	GameManager(OthelloBoard &othello);

	void gameLoop();

};