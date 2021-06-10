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
		void movement()
		{
			while (!dead)
			{
				for (int i = 0; i < 3; i++)
				{
					x = x + 1;
					Sleep(5000);
				}
				for (int i = 0; i < 3; i++)
				{
					x = x - 1;
					Sleep(5000);
				}
			}
		}
};

