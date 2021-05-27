#pragma once
#include "LevelItem.h"
class Gate :
	public LevelItem
{
protected:
	bool isOpen = false;

public:
	Gate(int _x, int _y) : LevelItem(_x, _y)
	{
		displayCharacter = ']';
		walkable = false;
		pickable = false;
	}

	void Open();
};

