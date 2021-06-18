#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include "player.h"
#include "Level.h"
#include "Weapon.h"
#include "Game.h"
#include "Portal.h"
#include "Button.h"
#include "Gate.h"
#include "Direction.h"
#include "json.hpp"

using namespace std;
using namespace nlohmann;

void levelSetup(vector<Level*>& allLevels);
void gameLoop(Game* game, Player* player, Level* levelPtr);
int getch_noblock();
Direction::Direction getInput();

int main()
{
	int width = 0;
	int height = 0;

	vector<Level*> allLevels;
	Level* levelPtr = nullptr;
	Player* player = new Player;

	levelSetup(allLevels);
	Level::setTargets();

	levelPtr = allLevels[0];
	player->setCurrentRoom(levelPtr);

	Game* game = new Game(player, levelPtr);

	gameLoop(game, player, levelPtr);
}

void gameLoop(Game* game, Player* player, Level* levelPtr)
{
	while (!game->getGameOver())
	{
		system("cls");
		if (player->getEnteredPassway())
		{
			levelPtr = player->getCurrentRoom()->getLevelAtDirection(player->getDirection());
			player->setCurrentRoom(levelPtr);
			player->setEnteredPassway(false);
			game->SetCurrentLevel(levelPtr);
		}

		levelPtr->DrawLevel(player->getX(), player->getY());
		game->UpdateGame(getInput());
	}
	system("cls");
	levelPtr->DrawLevel(player->getX(), player->getY());
	cout << "gg ez" << endl;
}

void levelSetup(vector<Level*>& allLevels)
{
	std::ifstream i("lvlsetup.json");
	json jsonLevels;
	i >> jsonLevels;
	for (auto& level : jsonLevels["levels"])
	{
		allLevels.push_back(new Level(level["name"]));
	}
	for (auto& level : jsonLevels["levels"])
	{
		for (auto& connection : level["connections"])
		{
			allLevels[level["index"]]->setLevelAtDirection(allLevels[connection["target"]], static_cast<Direction::Direction>(connection["direction"]));
		}
	}
}

int getch_noblock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

Direction::Direction getInput()
{
	char input = getch_noblock();

	switch (input)
	{
	case 'w':
	case 'W':
	{
		return Direction::Direction::Top;
		break;
	}
	case 's':
	case 'S':
	{
		return Direction::Direction::Bot;
		break;
	}
	case 'a':
	case 'A':
	{
		return Direction::Direction::Left;
		break;
	}
	case 'd':
	case 'D':
	{
		return Direction::Direction::Right;
		break;
	}
	}
}
