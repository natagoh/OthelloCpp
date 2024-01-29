#include "GameView.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>


GameView::GameView() : 
    _pieceBuffer(8.f), 
    _pieceRadius(32.f), 
    _boardSquareSize((_pieceRadius + _pieceBuffer) * 2 ), 
    _boardSize(8 * _boardSquareSize) {}


void GameView::renderGameGrid(sf::RenderWindow& window) {
   /*
   * + -- +
   * | XX |
   * | XX |
   * + -- +
   *
   * There is going to be some buffer between the piece and the square containing it
   */
    /*
    const float buffer = 8.f;
    const float pieceRadius = 32.f;
    const float boardSquareSize = (pieceRadius + buffer) * 2;
    const float boardSize = 8 * boardSquareSize;
    */ 
    // create a render texture for the board
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(_boardSize, _boardSize)) {
        printf("Error creating render texture\n");
    }

    // drawing uses the same functions
    renderTexture.clear();

    // draw board rectangle
    sf::RectangleShape boardRectangle(sf::Vector2f(_boardSize, _boardSize));
    sf::Color forestGreen = sf::Color(63, 90, 54);
    boardRectangle.setFillColor(forestGreen);
    renderTexture.draw(boardRectangle);
    renderTexture.display();

    for (int i = 1; i < 8; i++) {
        // draw horizontal board lines
        sf::Vertex horizontalLine[] = {
            sf::Vertex(sf::Vector2f(0.f, _boardSquareSize * i), sf::Color::Black),
            sf::Vertex(sf::Vector2f(_boardSize, _boardSquareSize * i), sf::Color::Black)
        };
        renderTexture.draw(horizontalLine, 2, sf::Lines);

        // draw vertical board lines
        sf::Vertex verticalLine[] = {
            sf::Vertex(sf::Vector2f(_boardSquareSize * i, 0.f), sf::Color::Black),
            sf::Vertex(sf::Vector2f(_boardSquareSize * i, _boardSize), sf::Color::Black)
        };
        renderTexture.draw(verticalLine, 2, sf::Lines);
    }

    // get the target texture (where the stuff has been drawn)
    const sf::Texture& boardTexture = renderTexture.getTexture();

    // draw game grid to the window
    sf::Sprite boardSprite(boardTexture);
    window.draw(boardSprite);
}

void GameView::renderPiece(sf::RenderWindow& window, Piece color, int row, int col) {
    // draw a circle
    sf::CircleShape piece(_pieceRadius);

    // set origin to be at center of circle
    piece.setOrigin(sf::Vector2f(_pieceRadius, _pieceRadius));

    // draw a circle at position (row, col) on the board
    const float rowPos = _boardSquareSize / 2 + _boardSquareSize * row;
    const float colPos = _boardSquareSize / 2 + _boardSquareSize * col;
    piece.setPosition(sf::Vector2f(colPos, rowPos));

    switch (color) {
        case Piece::Black: {
            piece.setFillColor(sf::Color::Black);
            window.draw(piece);
            break;
        }
        case Piece::White: {
            piece.setFillColor(sf::Color::White);
            piece.setOutlineColor(sf::Color::Black);
            piece.setOutlineThickness(1);
            window.draw(piece);
            break;
        }
        case Piece::Possible: {
            piece.setFillColor(sf::Color(0, 0, 0, 0.25 * 255));
            window.draw(piece);
            break;
        }
        case Piece::Empty: 
        default: {
            break;
        }
    }
}


void GameView::renderGameState(sf::RenderWindow& window, Piece board[8][8]) {
    // render the game grid
    renderGameGrid(window);

    // render the pieces
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            renderPiece(window, board[row][col], row, col);
        }
    }
}