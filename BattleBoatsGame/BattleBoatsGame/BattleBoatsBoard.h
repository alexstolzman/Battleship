#pragma once
#include "BattleBoat.h"
#include "iostream"
#include <vector>

using namespace std;

//Gameboard object
class BattleBoatsBoard
{
private:
	char board[10][10];
	vector<BattleBoat*> boats;	//vector of Battleboat references
	int turns=0;
	bool gameOver = false;
	bool debug = false;

public:
	BattleBoatsBoard();
	void displayBoard() const;
	void setUp();
	void generateBoard();
	void playerTurn(int x, int y);
	bool isGameOver() const;
	int getTurns() const;
	void debugMode(bool debug);
	int input(int max);
};

