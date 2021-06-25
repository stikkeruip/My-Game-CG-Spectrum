#pragma once
#include "Entity.h"

class Player;

class BasicEnemy : public Entity
{
	public:

		BasicEnemy(int _x, int _y) :Entity(_x, _y)
		{
			displayCharacter = 'E';
			mUpdateTimer = 0;
			mUpdateInterval = 120;
		}

		Direction::Direction Input();
		void Update();
};

