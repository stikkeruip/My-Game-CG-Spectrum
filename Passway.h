#pragma once
#include "Object.h"
#include "Direction.h"

class Player;

class Passway : public Object
{
protected:
	Direction::Direction passwayDirection;
	int targetX;
	int targetY;

public:
	int X;
	int Y;

	Passway(char c, Direction::Direction direction, int _x, int _y):Object(c), passwayDirection(direction), X(_x), Y(_y)
	{ 
		targetX = 0;
		targetY = 0;
		pickable = false;
		walkable = true;
	}

	void SetTarget(int x, int y){targetX = x; targetY = y;}
	virtual void InteractWith(Player* player);
};

