#pragma once

#include "Player.h"
#include "Level.h"

class Game
{
protected:
	Player& player;
	Level* level;
	bool gameOver;

public:
	Game(Player& _player, Level* _level):player(_player), level(_level)
	{
		gameOver = false;
	}

	void UpdatePlayerPosition();
	void SetCurrentLevel(Level* _level){ level = _level; }
	bool getGameOver() {return gameOver;}
};

