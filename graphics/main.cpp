#pragma once

#include <SFML/Graphics.hpp>
#include "GameView.h"
#include "GameManager.h"

int main()
{
    OthelloBoard othello = OthelloBoard();
    GameManager gameManager = GameManager(othello);
    gameManager.processGameLoop();

    return 0;
}