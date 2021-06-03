#pragma once
class Entity
{
protected:
	char displayCharacter;
	int health;
	int x;
	int y;

public:
	Entity(int _x, int _y) :displayCharacter('e'), x(_x), y(_y)
	{
		health = 20;
	}

	virtual char GetDisplayCharacter() { return displayCharacter; }
	virtual int getX() { return x; }
	virtual int getY() { return y; }
	virtual void setHealth(int x) { health -= x; }
	virtual void isDead() { if (health <= 0) displayCharacter = ' '; }
};

