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
	
	for (Entity* i : level->getEntityList())
	{
		i->Update();
	}

	/*case KEY_UP:
	{
		player->setHasAttacked(true);
		player->setAttackDir(Direction::Top);
		player->attack(Direction::Top);
		player->GetPositionAtDirection(Direction::Top, attackX, attackY);
		if (level->getEntityAt(attackX, attackY))
		{
			level->getEntityAt(attackX, attackY)->setHealth(player->hit());
			level->getEntityAt(attackX, attackY)->isDead();
		}
		break;
	}
	case KEY_DOWN:
	{
		player->setHasAttacked(true);
		player->setAttackDir(Direction::Bot);
		player->attack(Direction::Bot);
		player->GetPositionAtDirection(Direction::Bot, attackX, attackY);
		if (level->getEntityAt(attackX, attackY))
		{
			level->getEntityAt(attackX, attackY)->setHealth(player->hit());
			level->getEntityAt(attackX, attackY)->isDead();
		}
		break;
	}
	case KEY_LEFT:
	{
		player->setHasAttacked(true);
		player->setAttackDir(Direction::Left);
		player->attack(Direction::Left);
		player->GetPositionAtDirection(Direction::Left, attackX, attackY);
		if (level->getEntityAt(attackX, attackY))
		{
			level->getEntityAt(attackX, attackY)->setHealth(player->hit());
			level->getEntityAt(attackX, attackY)->isDead();
		}
		break;
	}
	case KEY_RIGHT:
	{
		player->setHasAttacked(true);
		player->setAttackDir(Direction::Right);
		player->attack(Direction::Right);
		player->GetPositionAtDirection(Direction::Right, attackX, attackY);
		if (level->getEntityAt(attackX, attackY))
		{
			level->getEntityAt(attackX, attackY)->setHealth(player->hit());
			level->getEntityAt(attackX, attackY)->isDead();
		}
		break;
	}
	default:
		break;
	}*/
}
