// OthelloCpp.cpp : Defines the entry point for the application.
//

#include "OthelloCpp.h"
#include "OthelloBoard.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	OthelloBoard othello = OthelloBoard();

	othello.printBoard();

	othello.getValidActions('X');

	printf("possible values for player X\n");
	othello.printBoard();

	return 0;
}
