#pragma once
#include <vector>
#include <Windows.h>
#include "Object.h"
#include "Direction.h"

using std::vector;

class Entity : public Object
{
protected:
	int health;
	bool dead = false;
	int mUpdateTimer;
	int mUpdateInterval;

public:
	

	Entity(int _x, int _y) : Object(_x, _y)
	{
		health = 20;
		displayCharacter = 'e';
	}

	virtual void setHealth(int x) { health -= x; }
	virtual void setDead();
	virtual bool isDead() { return dead; }
	virtual void GetPositionAtDirection(Direction::Direction direction, int& x, int& y);
	virtual void Update() {}
	virtual Direction::Direction Input() { return Direction::Direction::None; }
	
};

