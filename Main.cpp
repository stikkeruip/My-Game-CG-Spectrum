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

using namespace std;

void levelSetup(string txt, vector<Level>& allLevels);

int main()
{
	//A risky change

	int width = 0;
	int height = 0;

	vector<Level> allLevels;
	Level* levelPtr;

	//Is there a way to read all txt files in destination?

	Level middle("middle.txt");
	allLevels.push_back(middle);

	Level top("top.txt");
	allLevels.push_back(top);

	Level left("left.txt");
	allLevels.push_back(left);

	Level right("right.txt");
	allLevels.push_back(right);

	Level bot("bot.txt");
	allLevels.push_back(bot);

	levelSetup("lvlsetup.txt", allLevels);

	Level::setTargets();
	Player player;

	levelPtr = &allLevels[0];
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

void levelSetup(string txt, vector<Level>& allLevels)
{
	ifstream fname(txt);
	string temp;
	int lineIndex = 0;

	while (fname >> temp)
	{
		int pos;
		int dir;
		int count;

		fname >> temp;
		count = stoi(temp);
		for (int i = 0; i < count; i++)
		{
			fname >> temp;
			pos = stoi(temp);

			fname >> temp;
			dir = stoi(temp);

			allLevels[lineIndex].setLevelAtDirection(&allLevels[pos], static_cast<Direction>(dir));
		}
		getline(fname, temp);

		lineIndex++;
	}
}