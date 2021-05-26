#include <conio.h>
#include "Game.h"

void Game::UpdatePlayerPosition()
{
	char input = _getch();

	int newPlayerX = player.getPlayerX();
	int newPlayerY = player.getPlayerY();

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
		player.setHasAttacked(true);
		player.setAttackDir(Direction::Top);
		break;
	}
	case KEY_DOWN:
	{
		player.setHasAttacked(true);
		player.setAttackDir(Direction::Bot);
		break;
	}
	case KEY_LEFT:
	{
		player.setHasAttacked(true);
		player.setAttackDir(Direction::Left);
		break;
	}
	case KEY_RIGHT:
	{
		player.setHasAttacked(true);
		player.setAttackDir(Direction::Right);
		break;
	}
	default:
		break;
	}

	int index = level->GetIndexFromCoordinates(newPlayerX, newPlayerY);

	if (level->getContentAt(index) == ' ')
	{
		player.setPlayerX(newPlayerX);
		player.setPlayerY(newPlayerY);
	}
	else if (level->getContentAt(index) == '*')
	{
		player.setPlayerHasKey(true);
		level->setContentAt(index, ' ');
		player.setPlayerX(newPlayerX);
		player.setPlayerY(newPlayerY);
	}
	else if (level->getContentAt(index) == 'D' && player.getPlayerHasKey())
	{
		player.setPlayerHasKey(false);
		level->setContentAt(index, ' ');
		player.setPlayerX(newPlayerX);
		player.setPlayerY(newPlayerY);
	}
	else if (level->getContentAt(index) == 'X')
	{
		level->setContentAt(index, ' ');
		player.setPlayerX(newPlayerX);
		player.setPlayerY(newPlayerY);
		gameOver = true;
		return;
	}
	else if (level->getItemAt(index))
	{
		LevelItem* item = level->getItemAt(index);
		if (item->IsWalkable())
		{
			player.setPlayerX(newPlayerX);
			player.setPlayerY(newPlayerY);
		}
		item->InteractWith( &player );
		if (item->IsPickable())
		{
			level->clearItemAt(index);
		}
	}
}
