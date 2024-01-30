#include "GameManager.h"
#include <SFML/Window/Mouse.hpp>

GameManager::GameManager(OthelloBoard& othello) :
	_othello(othello),
	_gameView(GameView()) {
	const float boardSize = _gameView.getBoardSize();
	_window.create(sf::VideoMode(boardSize, boardSize, 32), "Othello", sf::Style::Titlebar | sf::Style::Close);
	_window.setFramerateLimit(60);
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

GameStepOutcome GameManager::processGameStep(
	const Player& player,
	bool isHuman,
	const std::optional<sf::Vector2i>& mousePos
) {
	//printf("player %c turn\n", player.color);

	auto actions = _othello.getValidActions((char)player.color);
	if (actions.empty()) {
		return GameStepOutcome::Action;
	}
	Piece board[8][8];
	Action action;

	if (isHuman) {
		// show the action hints
		_othello.enableActionHints(actions);
		//_othello.printBoard();

		// render the board with hints
		_othello.copyBoard(board);
		_gameView.renderGameState(_window, board);
		_window.display();

		auto humanAction = getHumanAction(actions, mousePos);
		if (!humanAction.has_value()) {
			return GameStepOutcome::Pending;
		}
		action = humanAction.value();
	}
	else {
		// add artificial delay for AI agent action
		if (_clock.getElapsedTime().asSeconds() <= 1) {
			return GameStepOutcome::Pending;
		}
		_clock.restart();

		// pick a random action
		int idx = rand() % actions.size();
		action = actions[idx];
	}

	printf("performing action\n");
	_othello.performAction(action);
	_othello.printBoard();

	// render the board after a move
	//_othello.copyBoard(board);
	//_gameView.renderGameState(_window, board);
	//_window.display();


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
		}
	}
}

void GameManager::processGameLoop() {
	int playerIdx = 0;

	sf::Clock clock;
	const int secondsPerFrame = 1;


	// run the program as long as the window is open
	while (_window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		pollWindowEvent();

		// clear the window with black color
		_window.clear(sf::Color::Black);

		// render initial board state
		Piece board[8][8];
		_othello.copyBoard(board);
		_gameView.renderGameState(_window, board);
		_window.display();

		

		// check for human board input
		const std::optional<sf::Vector2i> mouseClickPos = getMouseClickPos();

		if (_othello.isGameOver()) {
			printf("GAME OVER\n");
		}
		else {
			// player does an action
			// for now Human plays Black
			const auto player = _players[playerIdx];
			const auto gameStepOutcome = processGameStep(player, player.color == Piece::White, mouseClickPos);
			if (gameStepOutcome == GameStepOutcome::Action) {
				playerIdx++;
				playerIdx %= 2;
			}
		}

		// game tick
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() < secondsPerFrame) {
			pollWindowEvent();
		}
		clock.restart();
	}
}