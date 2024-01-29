#pragma once

#include <SFML/Graphics.hpp>
#include "GameView.h"

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
    
    othello.printBoard();

    auto actions = othello.getValidActions('X');

    printf("possible values for player X\n");
    Piece board[8][8];
    Piece originalBoard[8][8];
    othello.copyBoard(board);
    othello.copyBoard(originalBoard);

    // show actions on the board
    for (const auto& action : actions) {
        const int i = std::get<0>(action);
        const int j = std::get<1>(action);
        const Piece piece = std::get<2>(action);
        board[i][j] = Piece::Possible;
    }

    othello.setBoard(board);
    othello.printBoard();

    

    // GameManager gameManager = GameManager();
    GameView gameView = GameView();

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

        // draw game grid
        //gameView.renderGameGrid(window);

        // draw a game piece
        //gameView.renderPiece(window, Piece::Black, 2, 4);
      
        gameView.renderGameState(window, board);

        // end the current frame
        window.display();
    }

    return 0;
}