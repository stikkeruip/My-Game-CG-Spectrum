#pragma once

class BasicEnemy : public Entity
{
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
					x = x - 1;
					Sleep(5000);
				}
			}
		}
};

