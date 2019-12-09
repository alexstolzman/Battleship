#include "iostream"
#include "BattleBoatsBoard.h"
//Alex Stolzman
//This is the main class that should be run

using namespace std;
int main() {
	BattleBoatsBoard board;		//The gameboard
	int x, y;
	char debug;

	//Asks if the user wants to run debug mode. Repeats until it receives valid input
	do {
		cout << "Do you want to run in debug mode?(Y/N)\n";
		cin >> debug;
		debug = toupper(debug);	//Capitalizes letter if it lowercase
		if (debug == 'Y')
			board.debugMode(true);
		else
			board.debugMode(false);
	}
	while (debug != 'Y' && debug != 'N');

	board.setUp();	//Sets up board and boats vector
	system("CLS");	//Clears screen
	board.generateBoard();	//Randomly places boats on the board

	//Runs the game until the player sinks all of the boats
	do {
		board.displayBoard();	//Outputs board to screen

		cout << "Enter the x coordinate\n";
		x = board.input(10);

		cout << "Enter the y coordinate\n";
		y = board.input(10);

		system("CLS");
		board.playerTurn(x, y);		//Processes the player's turn
	} while (board.isGameOver() == false);


	//Outputs the number of turns it took to beat the game
	cout << "You beat the game in " << board.getTurns() << " turns!\n";

	return 0;
	}
