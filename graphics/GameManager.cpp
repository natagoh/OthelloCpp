#include "GameManager.h"
#include <SFML/Window/Mouse.hpp>
#include "../players/RandomPlayer.h"

GameManager::GameManager(OthelloBoard& othello) :
	_useOpponentDelay(true),
	_othello(othello),
	_gameView(GameView()) {
	const float boardSize = _gameView.getBoardSize();
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	_window.create(
		sf::VideoMode(boardSize, boardSize, 32),
		"Othello",
		sf::Style::Titlebar | sf::Style::Close,
		settings
	);
	_window.setVerticalSyncEnabled(true);

	// set window icon
	sf::Image icon;
	icon.loadFromFile("shaders/othello_icon.png");
	const sf::Vector2u iconSize = icon.getSize();
	_window.setIcon(iconSize.x, iconSize.y, icon.getPixelsPtr());
}

const std::optional<sf::Vector2i> GameManager::getMouseClickPos() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sf::Vector2i position = sf::Mouse::getPosition(_window);
		const float boardSquareSize = _gameView.getBoardSquareSize();
		const int row = position.y / boardSquareSize;
		const int col = position.x / boardSquareSize;
		printf("mouse board pos row: %i, col: %i\n", row, col);
		return position;
	}
	return std::nullopt;
}

const std::optional<Action> GameManager::getHumanAction(
	std::vector<Action> actions,
	std::optional<sf::Vector2i> mousePos
) {
	if (!mousePos.has_value()) {
		return std::nullopt;
	}

	sf::Vector2i position = sf::Mouse::getPosition(_window);
	const float boardSquareSize = _gameView.getBoardSquareSize();
	const int row = mousePos.value().y / boardSquareSize;
	const int col = mousePos.value().x / boardSquareSize;

	for (const auto& action : actions) {
		const auto& [i, j, _] = action;
		if (row == i && col == j) {
			return action;
		}
	}

	return std::nullopt;
}

GameStepOutcome GameManager::gameStep(
	std::shared_ptr<PlayerInterface> player,
	bool isHuman,
	const std::optional<sf::Vector2i>& mousePos
) {
	Action action;
	if (isHuman) {
		auto actions = _othello.getValidActions((char)player->getColor());
		if (actions.empty()) {
			// no valid actions, skip turn
			return GameStepOutcome::Action;
		}

		// show the action hints
		_othello.enableActionHints(actions);
		//_othello.printBoard();

		// render the board with hints
		_gameView.renderGameState(_window, _othello);
		//_window.display();

		const auto humanAction = getHumanAction(actions, mousePos);
		if (!humanAction.has_value()) {
			return GameStepOutcome::Pending;
		}
		action = humanAction.value();
	}
	else {
		// add artificial delay for AI agent action
		if (_useOpponentDelay && _clock.getElapsedTime().asSeconds() <= 1) {
			return GameStepOutcome::Pending;
		}
		_clock.restart();

		auto playerAction = player->getNextAction(_othello);
		if (!playerAction.has_value()) {
			// no valid actions, skip turn
			return GameStepOutcome::Action;
		}
		action = playerAction.value();
	}

	printf("performing action\n");
	_othello.performAction(action);
	_othello.printBoard();

	// render the board after a move?

	return GameStepOutcome::Action;
}

void GameManager::pollWindowEvent() {
	bool isMouseDragging = false;
	int lastDownX, lastDownY;

	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type) {
			// "close requested" event: we close the window
		case sf::Event::Closed:
			_window.close();
			break;

		case sf::Event::MouseMoved:
			if (isMouseDragging) {
				_window.setPosition(
					_window.getPosition()
					+ sf::Vector2<int>(event.mouseMove.x - lastDownX, event.mouseMove.y - lastDownY)
				);
			}
			break;
		case sf::Event::MouseButtonPressed:
			lastDownX = event.mouseButton.x;
			lastDownY = event.mouseButton.y;
			isMouseDragging = true;
			break;

		case sf::Event::MouseButtonReleased:
			isMouseDragging = false;
			break;

		default:
			break;
		}
	}
}

void GameManager::gameLoop() {
	int playerIdx = 0;

	sf::Clock clock;
	const int secondsPerFrame = 1;
	_useOpponentDelay = false;

	// list of players
	auto blackPlayer = std::make_shared<RandomPlayer>(Piece::Black);
	auto whitePlayer = std::make_shared<RandomPlayer>(Piece::White);

	std::vector<std::shared_ptr<PlayerInterface>> players;

	players.push_back(blackPlayer);
	players.push_back(whitePlayer);


	
	/*
	PlayerInterface players[2] = {
		RandomPlayer(Piece::Black),
		RandomPlayer(Piece::Black)
	};
	*/

	// run the program as long as the window is open
	while (_window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		pollWindowEvent();

		/*
		// game tick
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() < secondsPerFrame) {
			pollWindowEvent();
			continue;
		}
		clock.restart();
		*/

		// clear the window with black color
		_window.clear(sf::Color::Transparent);

		// check for human board input
		const std::optional<sf::Vector2i> mouseClickPos = getMouseClickPos();

		if (_othello.gameOver()) {
			_gameView.renderGameOver(_window, _othello);
			continue;
		}
		else {
			// render board state
			_gameView.renderGameState(_window, _othello);

			// player does an action
			// for now Human plays Black
			auto player = players[playerIdx];
			//const auto gameStepOutcome = gameStep(player, player.color == Piece::Black, mouseClickPos);
			const auto gameStepOutcome = gameStep(player);
			if (gameStepOutcome == GameStepOutcome::Action) {
				playerIdx++;
				playerIdx %= 2;
			}
		}
	}
}