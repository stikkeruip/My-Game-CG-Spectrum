#pragma once
#include <Windows.h>
#include <vector>

using std::vector;

class Entity
{
protected:
	char displayCharacter;
	int health;
	int x;
	int y;
	bool dead = false;

public:
	static vector<Entity*> entityList;

	Entity(int _x, int _y) :displayCharacter('e'), x(_x), y(_y)
	{
		health = 20;
	}

	virtual char GetDisplayCharacter() { return displayCharacter; }
	virtual int getX() { return x; }
	virtual int getY() { return y; }
	virtual void setHealth(int x) { health -= x; }
	virtual void isDead();
	virtual void movement();
};

