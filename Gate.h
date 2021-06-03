#pragma once
#include "LevelItem.h"
class Gate :
	public LevelItem
{
protected:
	bool isOpen = false;
	int id;

public:
	Gate(int _x, int _y) : LevelItem(_x, _y)
	{
		displayCharacter = ']';
		walkable = false;
		pickable = false;
		id = 0;
	}

	void Open();
	int getID() { return id; };
	void setID(int x) { id = x; };
};

