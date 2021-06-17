#pragma once
#include <vector>

using std::vector;

class Entity : public Object
{
protected:
	int health;
	bool dead = false;

public:
	static vector<Entity*> entityList;

	Entity(int _x, int _y) : Object(_x, _y)
	{
		health = 20;
		displayCharacter = 'e';
	}

	virtual void setHealth(int x) { health -= x; }
	virtual void isDead();
	virtual void GetPositionAtDirection(Direction direction, int& x, int& y);
};

