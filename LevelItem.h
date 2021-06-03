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
	int id = 0;
public:
	LevelItem(char c) : displayCharacter(c)
	{ 
		pickable = false;
		walkable = false;
		x = -1;
		y = -1;
	}
	LevelItem(int _x, int _y) : displayCharacter('0'), x(_x), y(_y)
	{
		pickable = false;
		walkable = false;
	}
	virtual char GetDisplayCharacter() { return displayCharacter; }
	virtual bool IsPickable() { return pickable; }
	virtual bool IsWalkable() { return walkable; }
	virtual int getX() { return x; }
	virtual int getY() { return y; }
	virtual void InteractWith( Player* player ) {}
	virtual int getID() { return id; };
	virtual void setID(int x) { id = x; };
};

