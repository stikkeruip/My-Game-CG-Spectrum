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

void Game::UpdateGame(Direction::Direction pInput)
{
	char input = getch_noblock();

	int newX;
	int newY;
	int attackX;
	int attackY;

	Player* p;
	Direction::Direction mInput;
	int index = level->GetIndexFromCoordinates(newX, newY);
	for (Entity* i : Entity::entityList)
	{
		newX = i->getX();
		newY = i->getY();
		attackX = i->getX();
		attackY = i->getY();

		if (p = dynamic_cast<Player*>(i))
		{
			mInput = pInput;
			player = p;
		}

		mInput = entityMovement();

		switch (mInput)
		{
		case Direction::Direction::Top:
		{
			newY--;
			if (player && player->getTeleported())
				player->changeTeleportState();
			break;
		}
		case Direction::Direction::Bot:
		{
			newY++;
			if (player && player->getTeleported())
				player->changeTeleportState();
			break;
		}
		case Direction::Direction::Left:
		{
			newX--;
			if (player && player->getTeleported())
				player->changeTeleportState();
			break;
		}
		case Direction::Direction::Right:
		{
			newX++;
			if (player && player->getTeleported())
				player->changeTeleportState();
			break;
		}

		if (level->getContentAt(index) == ' ')
		{
			i->setX(newX);
			i->setY(newY);
		}

		if (player)
		{
			if (level->getContentAt(index) == '*')
			{
				player->setPlayerHasKey(true);
				level->setContentAt(index, ' ');
				player->setX(newX);
				player->setY(newY);
			}
			else if (level->getContentAt(index) == 'D' && player->getPlayerHasKey())
			{
				player->setPlayerHasKey(false);
				level->setContentAt(index, ' ');
				player->setX(newX);
				player->setY(newY);
			}
			else if (level->getContentAt(index) == 'X')
			{
				level->setContentAt(index, ' ');
				player->setX(newX);
				player->setY(newY);
				gameOver = true;
				return;
			}
			else if (level->getItemAt(index))
			{
				Object* item = level->getItemAt(index);
				if (item->IsWalkable())
				{
					player->setX(newX);
					player->setY(newY);
				}
				item->InteractWith(player);
				if (item->IsPickable())
				{
					level->clearItemAt(index);
				}
			}
		}
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
