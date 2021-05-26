#pragma once
#include "LevelItem.h"
class Passway :
	public LevelItem
{
protected:
	Direction passwayDirection;
	int targetX;
	int targetY;

public:
	int X;
	int Y;

	Passway(char c, Direction direction, int _x, int _y):LevelItem(c), passwayDirection(direction), X(_x), Y(_y)
	{ 
		targetX = 0;
		targetY = 0;
		pickable = false;
		walkable = true;
	}

	void SetTarget(int x, int y){targetX = x; targetY = y;}
	virtual void InteractWith(Player* player);
};

