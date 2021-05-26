#pragma once
#include "LevelItem.h"
class Portal :
	public LevelItem
{
protected:
	Portal* targetPortal;

public:
	Portal(int _x, int _y) : LevelItem(_x, _y)
	{
		pickable = false;
		walkable = true;
		targetPortal = nullptr;
	}

	void SetTarget(Portal* portal){ targetPortal = portal; }
	virtual void InteractWith(Player* player);
};

