#include <conio.h>
#include "Game.h"

int Game::getch_noblock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

void Game::UpdateGame(Direction input)
{
	char input = getch_noblock();


	int newPlayerX = player->getX();
	int newPlayerY = player->getY();
	int attackX = player->getX();
	int attackY = player->getY();

	switch (input)
	{
	case Direction::Top:
	{
		newPlayerY--;
		if (player->getTeleported())
			player->changeTeleportState();
		break;
	}
	case Direction::Bot:
	{
		newPlayerY++;
		if (player->getTeleported())
			player->changeTeleportState();
		break;
	}
	case Direction::Left:
	{
		newPlayerX--;
		if (player->getTeleported())
			player->changeTeleportState();
		break;
	}
	case Direction::Right:
	{
		newPlayerX++;
		if (player->getTeleported())
			player->changeTeleportState();
		break;
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

	int index = level->GetIndexFromCoordinates(newPlayerX, newPlayerY);

	if (level->getContentAt(index) == ' ')
	{
		player->setX(newPlayerX);
		player->setY(newPlayerY);
	}
	else if (level->getContentAt(index) == '*')
	{
		player->setPlayerHasKey(true);
		level->setContentAt(index, ' ');
		player->setX(newPlayerX);
		player->setY(newPlayerY);
	}
	else if (level->getContentAt(index) == 'D' && player->getPlayerHasKey())
	{
		player->setPlayerHasKey(false);
		level->setContentAt(index, ' ');
		player->setX(newPlayerX);
		player->setY(newPlayerY);
	}
	else if (level->getContentAt(index) == 'X')
	{
		level->setContentAt(index, ' ');
		player->setX(newPlayerX);
		player->setY(newPlayerY);
		gameOver = true;
		return;
	}
	else if (level->getItemAt(index))
	{
		Object* item = level->getItemAt(index);
		if (item->IsWalkable())
		{
			player->setX(newPlayerX);
			player->setY(newPlayerY);
		}
		item->InteractWith( player );
		if (item->IsPickable())
		{
			level->clearItemAt(index);
		}
	}
}
