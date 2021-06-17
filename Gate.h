#pragma once
#include "Object.h"
class Gate :
	public Object
{
protected:
	bool isOpen = false;
	int id;

public:
	Gate(int _x, int _y) : Object(_x, _y)
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

