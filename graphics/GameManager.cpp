#include "GameManager.h"
#include "GameView.h"

GameManager::GameManager() {}

/*
void GameManager::renderGameState(Piece board[8][8]) {

   
   auto actions = _othello.getValidActions('X');

   printf("possible values for player X\n");
   Piece board[8][8];
   Piece originalBoard[8][8];
   _othello.copyBoard(board);
   _othello.copyBoard(originalBoard);

   // show actions on the board
   for (const auto& action : actions) {
       const int i = std::get<0>(action);
       const int j = std::get<1>(action);
       const Piece piece = std::get<2>(action);
       board[i][j] = Piece::Possible;
   }

   _othello.setBoard(board);
   _othello.printBoard();

  
}
*/