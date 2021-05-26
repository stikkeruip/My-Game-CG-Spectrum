#pragma once
#include "Player.h"

class LevelItem
{
protected:
	char displayCharacter;
	bool walkable;
	bool pickable;
	int x;
	int y;
public:
	LevelItem(char c) : displayCharacter(c)
	{ 
		pickable = false;
		walkable = false;
		x = -1;
		y = -1;
	}
	LevelItem(int _x, int _y) : x(_x), y(_y)
	{
		displayCharacter = '0';
		pickable = false;
		walkable = false;
	}
	LevelItem(char c, int _x, int _y) : displayCharacter(c), x(_x), y(_y)
	{
		pickable = false;
		walkable = false;
	}
	virtual char GetDisplayCharacter() { return displayCharacter; }
	virtual bool IsPickable() { return pickable; }
	virtual bool IsWalkable() { return walkable; }
	int getX() { return x; }
	int getY() { return y; }
	virtual void InteractWith( Player* player ) {}
};

