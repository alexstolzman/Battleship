#include "BattleBoat.h"


//Constructor: takes length and sets up hits array
BattleBoat::BattleBoat(int length) {
	
	this->length = length;
	hits[length];

	for (int i = 0; i < length; i++) {
		hits[i] = false;
	}
}

//Getter for the starting x position
int BattleBoat::getX() const {
	return startX;
}

//Getter for the starting y position
int BattleBoat::getY() const {
	return startY;
}

//Getter for the boat's length
int BattleBoat::getLength() const {
	return length;
}

//Returns whether the boat is vertical or not
bool BattleBoat::isVertical() const {
	return vertical;
}

//Determines whether the boat was hit
bool BattleBoat::isHit(int x, int y) const{
	if (vertical == true) {
		if (startX==x && (startY<=y && y<length+startY)) {		//Determines if the point is within the length of the boat
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (startY==y && (startX <= x && x< length + startX)) {	//Determines if tjhe point if within the length of the boat
			return true;
		}
		else {
			return false;
		}
	}
	
}

//Records a hit on the boat
void BattleBoat::hit(int x, int y) {
	if (vertical == true) {
		hits[y - startY] = true;	//Marks the array position as hit(true)
	}
	else {
		hits[x - startX] = true;	//Marks the array position as hit(true)
	}
}

//Determines whether the boat is sunk
bool BattleBoat::isSunk() const {
	
	//Iterates through the array to see which point shave been hit
	for (int i = 0; i < length; i++) {
		if (hits[i] == false) {	
			return false;	//Returns false if a point hasn't been hit yet
		}
	}
	return true;	//Returns true if all points have been hit

}

//Sets the starting position
void BattleBoat::setStart(int x, int y) {
	startX = x;
	startY = y;
}

//Sets the boat's orientation
void BattleBoat::setVertical(bool vertical) {
	this->vertical = vertical;
}
