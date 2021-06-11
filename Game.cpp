#include <conio.h>
#include "Game.h"

int Game::getch_noblock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

void Game::UpdatePlayerPosition()
{
	char input = getch_noblock();

	int newPlayerX = player->getPlayerX();
	int newPlayerY = player->getPlayerY();
	int attackX = player->getPlayerX();
	int attackY = player->getPlayerY();

	switch (input)
	{
	case 'w':
	case 'W':
	{
		newPlayerY--;
		break;
	}
	case 's':
	case 'S':
	{
		newPlayerY++;
		break;
	}
	case 'a':
	case 'A':
	{
		newPlayerX--;
		break;
	}
	case 'd':
	case 'D':
	{
		newPlayerX++;
		break;
	}
	case KEY_UP:
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
	}

	int index = level->GetIndexFromCoordinates(newPlayerX, newPlayerY);

	if (level->getContentAt(index) == ' ')
	{
		player->setPlayerX(newPlayerX);
		player->setPlayerY(newPlayerY);
	}
	else if (level->getContentAt(index) == '*')
	{
		player->setPlayerHasKey(true);
		level->setContentAt(index, ' ');
		player->setPlayerX(newPlayerX);
		player->setPlayerY(newPlayerY);
	}
	else if (level->getContentAt(index) == 'D' && player->getPlayerHasKey())
	{
		player->setPlayerHasKey(false);
		level->setContentAt(index, ' ');
		player->setPlayerX(newPlayerX);
		player->setPlayerY(newPlayerY);
	}
	else if (level->getContentAt(index) == 'X')
	{
		level->setContentAt(index, ' ');
		player->setPlayerX(newPlayerX);
		player->setPlayerY(newPlayerY);
		gameOver = true;
		return;
	}
	else if (level->getItemAt(index))
	{
		LevelItem* item = level->getItemAt(index);
		if (item->IsWalkable())
		{
			player->setPlayerX(newPlayerX);
			player->setPlayerY(newPlayerY);
		}
		item->InteractWith( player );
		if (item->IsPickable())
		{
			level->clearItemAt(index);
		}
	}
}
