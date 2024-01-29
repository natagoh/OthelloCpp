#include "GameManager.h"
#include <SFML/Window/Mouse.hpp>

GameManager::GameManager(OthelloBoard &othello) : 
    _othello(othello), 
    _gameView(GameView()),
    _window(sf::VideoMode(1080u, 1080u, 32), "Othello") {
    const float boardSize = _gameView.getBoardSize();
    // _window.setSize(sf::Vector2u(boardSize, boardSize));
    _window.setFramerateLimit(60);
}

std::optional<Action> GameManager::getHumanAction(std::vector<Action> actions) {
    // figure out which square the mouse is clicking
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i position = sf::Mouse::getPosition(_window);
        const float boardSquareSize = _gameView.getBoardSquareSize();
        const int row = position.y / boardSquareSize;
        const int col = position.x / boardSquareSize;

        for (const auto& action : actions) {
            const auto &[i, j, _] = action;
            if (row == i && col == j) {
                return action;
            }
        }
    }
   
    return std::nullopt;
}

void GameManager::processGameStep(const Player &player, bool isHuman) {
	printf("player %c turn\n", player.color);
	auto actions = _othello.getValidActions((char)player.color);
    if (actions.empty()) {
        return;
    }
    Piece board[8][8];
    Action action;
    if (isHuman) {
        // show the action hints
        _othello.enableActionHints(actions);
        _othello.printBoard();

        // render the board with hints
        _othello.copyBoard(board);
        _gameView.renderGameState(_window, board);
        _window.display();

        auto humanAction = getHumanAction(actions);
        while (!humanAction.has_value()) {
            humanAction = getHumanAction(actions);
        }
        action = humanAction.value();
    }
    else {

        // pick a random action
        int idx = rand() % actions.size();
        action = actions[idx];
    }

	
	_othello.performAction(action);
	_othello.printBoard();

    // render the board after a move
    _othello.copyBoard(board);
    _gameView.renderGameState(_window, board);
    _window.display();


    // delay for some time

    // starts the clock
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() <= 1) {
        continue;
    }
    clock.restart();

}

void GameManager::processGameLoop() {
    int playerIdx = 0;

    // run the program as long as the window is open
    while (_window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (_window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        // clear the window with black color
        _window.clear(sf::Color::Black);

        // render current board state
        Piece board[8][8];
        _othello.copyBoard(board);
        _gameView.renderGameState(_window, board);
        _window.display();

        if (_othello.isGameOver()) {
            printf("GAME OVER\n");
        } else {
            // player does an action
            // for now Human plays Black
            const auto player = _players[playerIdx];
            processGameStep(player, player.color == Piece::Black);
            playerIdx++;
            playerIdx %= 2;
        }
    }
}