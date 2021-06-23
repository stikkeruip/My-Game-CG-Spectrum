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
	levelPtr->setEntityList(player);

	Game* game = new Game(player, levelPtr);

	gameLoop(game, player, levelPtr);
}

void gameLoop(Game* game, Player* player, Level* levelPtr)
{
	while (!player->hasReachedEnd())
	{
		system("cls");
		if (player->getEnteredPassway())
		{
			levelPtr->removeEntity(player);
			levelPtr = Object::getCurrentRoom()->getLevelAtDirection(player->getDirection());
			Object::setCurrentRoom(levelPtr);
			player->setEnteredPassway(false);
			game->SetCurrentLevel(levelPtr);
			levelPtr->setEntityList(player);
		}

		levelPtr->DrawLevel(player->getX(), player->getY());
		game->UpdateGame();
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
