#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <fstream>
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

void levelSetup(vector<Level*> &allLevels);

int main()
{

	int width = 0;
	int height = 0;

	vector<Level*> allLevels;
	Level* levelPtr = nullptr;

	levelSetup(allLevels);

	Level::setTargets();
	Player player;

	levelPtr = allLevels[0];
	player.setCurrentRoom(levelPtr);
	Game game(player, levelPtr);

	while (!game.getGameOver())
	{
		system("cls");
		if (player.getEnteredPassway())
		{
			levelPtr = player.getCurrentRoom()->getLevelAtDirection(player.getDirection());
			player.setCurrentRoom(levelPtr);
			player.setEnteredPassway(false);
			game.SetCurrentLevel(levelPtr);
		}
		if (player.GetHasAttacked())
		{
			player.setHasAttacked(false);
			//todo with attack
		}

		levelPtr->DrawLevel(player.getPlayerX(), player.getPlayerY());
		game.UpdatePlayerPosition();
	}
	system("cls");
	levelPtr->DrawLevel(player.getPlayerX(), player.getPlayerY());
	cout << "gg ez" << endl;
}

void levelSetup(vector<Level*> &allLevels)
{
	int indexLvl;
	int connLvl;
	int connDir;
	string lvlName;
	std::ifstream i("lvlsetup.json");
	json jsonLevels;
	i >> jsonLevels;
	for (auto& level : jsonLevels["levels"])
	{
		lvlName = level["name"];
		lvlName.append(".txt");
		allLevels.push_back(new Level(lvlName));
	}
	for (auto& level : jsonLevels["levels"])
	{
		for (auto& connection : level["connections"])
		{
			indexLvl = level["index"];
			connLvl = connection["target"];
			connDir = connection["direction"];
			allLevels[indexLvl]->setLevelAtDirection(allLevels[connLvl], static_cast<Direction>(connDir));
		}
	}
}