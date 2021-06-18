#pragma once

#include "Level.h"
#include "Object.h"
#include "Direction.h"

class Game
{

protected:
	Player* player;
	Level* level;
	Entity* entity;
	bool gameOver;

public:
	Game(Player* _player, Level* _level):player(_player), level(_level)
	{
		gameOver = false;
	}

	void UpdateGame(Direction::Direction input);
	void SetCurrentLevel(Level* _level){ level = _level; }
	bool getGameOver() {return gameOver;}
	Direction::Direction entityMovement();
	int getch_noblock();
};

