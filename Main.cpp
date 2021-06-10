#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <thread>
#include "Player.h"
#include "Level.h"
#include "Weapon.h"
#include "Game.h"
#include "Portal.h"
#include "Button.h"
#include "Gate.h"
#include "json.hpp"

using namespace std;
using namespace nlohmann;

void levelSetup(vector<Level*>& allLevels);
void gameLoop();
void moveEntities();

vector<Level*> allLevels;
Level* levelPtr = nullptr;
Player player;
Game* game = nullptr;

int main()
{

	int width = 0;
	int height = 0;

	levelSetup(allLevels);
	Level::setTargets();

	levelPtr = allLevels[0];
	player.setCurrentRoom(levelPtr);

	game = new Game(player, levelPtr);

	std::thread th1(gameLoop);
	std::thread th2(moveEntities);

	th1.join();
	th2.join();
}

void gameLoop()
{
	while (!game->getGameOver())
	{
		system("cls");
		if (player.getEnteredPassway())
		{
			levelPtr = player.getCurrentRoom()->getLevelAtDirection(player.getDirection());
			player.setCurrentRoom(levelPtr);
			player.setEnteredPassway(false);
			game->SetCurrentLevel(levelPtr);
		}

		levelPtr->DrawLevel(player.getPlayerX(), player.getPlayerY());
		game->UpdatePlayerPosition();
	}
	system("cls");
	levelPtr->DrawLevel(player.getPlayerX(), player.getPlayerY());
	cout << "gg ez" << endl;
}

void moveEntities()
{
	for (Entity* e : Entity::entityList)
	{
		e->movement();
	}
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
			allLevels[level["index"]]->setLevelAtDirection(allLevels[connection["target"]], static_cast<Direction>(connection["direction"]));
		}
	}
}