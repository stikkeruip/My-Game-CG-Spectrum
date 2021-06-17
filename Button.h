#pragma once
#include "Object.h"
#include "Gate.h"
#include "Player.h"

class Button : public Object
{
protected:
	Gate* gate = nullptr;

public:
	Button(int _x, int _y) : Object(_x, _y)
	{
		displayCharacter = 'B';
		walkable = true;
		pickable = false;
	}
	virtual void InteractWith(Player* player);
	void SetTargetGate(Gate* _gate) {gate = _gate;}
};

