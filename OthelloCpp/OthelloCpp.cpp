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

	return 0;
}
