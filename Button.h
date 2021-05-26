#pragma once
#include "LevelItem.h"

class Gate;

class Button :
	public LevelItem
{
protected:
	Gate* gate = nullptr;

public:
	Button(int _x, int _y) : LevelItem(_x, _y)
	{
		walkable = true;
		pickable = false;
	}
	virtual void InteractWith(Player* player);
	void SetTargetGate(Gate* _gate) {gate = _gate;}
};

