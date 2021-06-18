#pragma once
#include "Object.h"

class Player;

class Portal : public Object
{
protected:
	Portal* targetPortal;
	int id;
public:
	Portal(int _x, int _y) : Object(_x, _y)
	{
		id = 0;
		displayCharacter = 'O';
		pickable = false;
		walkable = true;
		targetPortal = nullptr;
	}

	void SetTarget(Portal* portal){ targetPortal = portal; }
	virtual void InteractWith(Player* player);
	int getID() { return id; };
	void setID(int x) { id = x; };
};

