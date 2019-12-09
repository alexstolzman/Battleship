#include "BattleBoatsBoard.h"
#include "iostream"
#include "cstdlib"
#include "ctime"

using namespace std;

//Constructor; sets up gameboard
BattleBoatsBoard::BattleBoatsBoard()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = 'O';
		}
	}
}

//Displays board
void BattleBoatsBoard::displayBoard() const {
	cout << "      0   1   2   3   4   5   6   7   8   9\n\n";

	//Iterates twice if user is in debug mode
	for (int k = 0; k < 1 + debug; k++) {	
		for (int i = 0; i < 10; i++) {
			cout << i << "     ";
			for (int j = 0; j < 10; j++) {
				if (board[j][i] == '-')
				{
					if(k!=1)	//Outputs non-debug mode board
						cout << "O" << "   ";
					else
						cout << board[j][i] << "   ";
				}
				else {
					cout << board[j][i] << "   ";
				}
			}
			cout << endl << endl;;
		}
		cout << endl << endl;
	}
}

//Function for setting up the number and size of boats
void BattleBoatsBoard::setUp() {
	int boatInfo,boatSize;
	int sum = 0;

	cout << "Enter the number of boats(no more than 10): " << endl;
	boatInfo = this->input(10);	//Validates input

	cout << "Enter boat sizes. \n";
	cout << "Each boat must be no larger than 6 squares, and the the sum of all sizes should be no greater than 20. \n";

	do {
		sum = 0;
		boats.clear();	//Clears vector 

		for (int i = 1; i <= boatInfo; i++) {
			cout << "\nBoat " << i << " Size: \n";
			cout << "Current sum: " << sum << endl;

			boatSize = this->input(6);
			sum += boatSize;	//Keeps track of total of boat sizes


			boats.push_back(new BattleBoat(boatSize));	//Adds new boat to vector
		}
		
	} while (sum > 20);
	
	
}

//Randomly places boats on board
void BattleBoatsBoard::generateBoard() {
	bool valid = true;
	int ranX;
	int ranY;
	int ranDirection;

	srand(time(NULL));	//Seeds the random number generator using the current time

	//Iterates through list of boats
	for (int i = 0; i < boats.size(); i++) {
		//Repeats until the boat is in a valid position
		do {
			valid = true;
			ranX = rand() % 10;	//x=0-9
			ranY = rand() % 10;	//y=0-9
			ranDirection = rand() % 2;

			//sets the boat's orientation based on a randomized number
			boats[i]->setVertical(ranDirection);

			//Sets start coordinates for the boat
			boats[i]->setStart(ranX, ranY);

			//Makes sure the boat is within the bounds of the board
			if (((boats[i]->isVertical()==true && (ranY+boats[i]->getLength())<10) || (boats[i])->isVertical() == false && ranX + boats[i]->getLength() < 10)){
				
				//checks to make sure the boat doesn't overlap with any existing boats; if it does, breaks the loop and starts over
				for (int j = 0; j < boats[i]->getLength(); j++) {
					if (boats[i]->isVertical() == true) {
						if (board[boats[i]->getX()][boats[i]->getY() + j] == '-') {
							valid = false;
							break;
						}
					}
					else {
						if (board[boats[i]->getX() + j][boats[i]->getY()] == '-') {
							valid = false;
							break;
						}
					}
				}
			}
			else {
				valid = false;
			}

			//if the boat is valid, stores its location on the board
			if (valid == true) {
				for (int j = 0; j < boats[i]->getLength(); j++) {
					if (boats[i]->isVertical() == true) {
						board[boats[i]->getX()][boats[i]->getY() + j] = '-';
					}
					else {
						board[boats[i]->getX() + j][boats[i]->getY()] = '-';
					}
				}
			}

		} while (valid == false);
	}
}

//Determines whether the player hit or missed a boat
void BattleBoatsBoard::playerTurn(int x, int y) {

	if (board[x][y] == 'O') {
		board[x][y] = 'X';
		cout << "Miss!\n\n";	//Outputs "Miss" if the location is empty
	}
	else if (board[x][y] == 'X' || board[x][y] == '*') {
		cout << "Penalty!\n\n";	//Outputs "penalty" if the location was already hit
	}
	else {
		board[x][y] = '*';
		cout << "Hit!\n\n";	//Outputs "hit" if the player hits a boat

		//Iterates through the boats
		for (int i = 0; i < boats.size(); i++) {
			if (boats[i]->isHit(x,y)) {	//If the boat is hit, mark the position
				boats[i]->hit(x, y);

				//if the boat is sunk, output a message to the screen
				if (boats[i]->isSunk()) {
					cout << "You sunk a boat!\n";
				}
			}
			
		}
	}
	turns += 1;
}

//Determines whether the game is over
bool BattleBoatsBoard::isGameOver() const {
	
	//Iterates through the vector of boats and determines if all of them have been sunk
	for (int i = 0; i < boats.size(); i++) {
		if (boats[i]->isSunk() == false) {
			return false;
		}
	}
	return true;
}

//Returns number of turns
int BattleBoatsBoard::getTurns() const {
	return turns;
}

//Starts the game in debug mode
void BattleBoatsBoard::debugMode(bool debug) {
	this->debug = debug;
}

//Validates user input
int BattleBoatsBoard::input(int max) {
	double input = 0;
	cin >> input;

	//Makes sure input is less than the max value and an integer
	while (input > max || input < 0 || cin.fail() || floor(input) != ceil(input))
	{
		cin.clear();
		cin.ignore(256, '\n');	//clears buffer
		cin >> input;
	}

	return input;
}
