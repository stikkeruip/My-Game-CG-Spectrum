#pragma once
#include "Entity.h"

class BasicEnemy:
	public Entity
{
	protected:

	public:
		BasicEnemy(int _x, int _y) :Entity(_x, _y)
		{
			displayCharacter = 'E';
		}
};

