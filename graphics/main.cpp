#pragma once

#include <SFML/Graphics.hpp>
#include "GameView.h"
#include "GameManager.h"

int main()
{
    // create the window
    auto window = sf::RenderWindow{ { 1080u, 1080u }, "Othello" };
    window.setFramerateLimit(60);


    /*
    * + -- +
    * | XX |
    * | XX |
    * + -- +
    * 
    * There is going to be some buffer between the piece and the square containing it
    */
    const float buffer = 8.f;
    const float pieceRadius = 32.f;
    const float boardSquareSize = (pieceRadius + buffer) * 2;
    const float boardSize = 8 * boardSquareSize;

    
  
    OthelloBoard othello = OthelloBoard();
    
    /*
    othello.printBoard();

    auto actions = othello.getValidActions('X');

    printf("possible values for player X\n");

    othello.enableActionHints(actions);

    Piece board[8][8];
    othello.copyBoard(board);
    othello.printBoard();
    */
    

    GameManager gameManager = GameManager(othello);
    GameView gameView = GameView();

    gameManager.processGameLoop();

    // run the program as long as the window is open
    /*
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
           
        
        Piece board[8][8];
        othello.copyBoard(board);
        gameView.renderGameState(window, board);

        // figure out which square the mouse is clicking
        sf::Vector2i position = sf::Mouse::getPosition(window);
        printf("mouse pos: %i, %i\n", position.x, position.y);
        // end the current frame
        window.display();
    }
    */

    return 0;
}