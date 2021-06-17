#pragma once

#include "player.h"
#include "Level.h"
#include "Entity.h"

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

	void UpdateGame(Direction input);
	void SetCurrentLevel(Level* _level){ level = _level; }
	bool getGameOver() {return gameOver;}
	int getch_noblock();
};

