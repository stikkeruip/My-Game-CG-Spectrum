#include <conio.h>
#include "Game.h"

int Game::getch_noblock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

Direction::Direction Game::entityMovement()
{
	int dir = rand() % (3 - 0 + 1) + 0;
	if (dir == 0)
	{
		return Direction::Top;
	}
	else if (dir == 1)
	{
		return Direction::Right;
	}
	else if (dir == 2)
	{
		return Direction::Bot;
	}
	else if (dir == 3)
	{
		return Direction::Left;
	}
}

void Game::UpdateGame()
{
	
	for (Entity* i: level->getLevelEntities())
	{
		if (i && !i->isDead())
		{
			i->Update();
			Sleep(30);
		}
	}
}
