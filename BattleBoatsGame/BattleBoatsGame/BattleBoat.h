#pragma once
//boat object class
class BattleBoat
{
private:
	int length;
	int startX;
	int startY;
	bool vertical;
	bool hits[];	//Array of points in the boat; keeps track of whether thet have been hit or not

public:
	BattleBoat(int length);
	int getX() const;
	int getY() const;
	int getLength() const;
	bool isVertical() const;
	bool isHit(int x, int y) const;
	bool isSunk() const;
	void setStart(int x, int y);
	void setVertical(bool vertical);
	void hit(int x, int y);
};

