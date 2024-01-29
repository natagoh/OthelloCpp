#include "GameManager.h"
#include "GameView.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

GameManager::GameManager(OthelloBoard &othello) : _othello(othello) {}

void GameManager::processGameStep(const Player &player) {
	printf("player %c turn\n", player.color);
	auto actions = _othello.getValidActions((char)player.color);
    if (actions.empty()) {
        return;
    }

	// show the action hints
	_othello.enableActionHints(actions);
	_othello.printBoard();

	// pick a random action
	int idx = rand() % actions.size();
	Action action = actions[idx];

	_othello.performAction(action);
	_othello.printBoard();

}

void GameManager::processGameLoop() {
	// create the window
	auto window = sf::RenderWindow{ { 1080u, 1080u }, "Othello" };
	window.setFramerateLimit(60);


    GameView gameView = GameView();

    // starts the clock
    sf::Clock clock; 

    int playerIdx = 0;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // render current board state
        Piece board[8][8];
        _othello.copyBoard(board);
        gameView.renderGameState(window, board);

        // measure time elapsed
        float elapsedSeconds = clock.getElapsedTime().asSeconds();
        if (elapsedSeconds <= 1) {
            window.display();
            continue;
        }
        clock.restart();

        if (_othello.isGameOver()) {
            printf("GAME OVER\n");
        } else {
            // player does an action
            processGameStep(_players[playerIdx]);
            playerIdx++;
            playerIdx %= 2;
        }

        // figure out which square the mouse is clicking
        sf::Vector2i position = sf::Mouse::getPosition(window);
        printf("mouse pos: %i, %i\n", position.x, position.y);
        // end the current frame
       
    }
}