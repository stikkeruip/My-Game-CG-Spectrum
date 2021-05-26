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

int main()
{
	//I'm going to edit from my side
	//So you will get a confliction
	//And I want you to resolve it by keeping both changes from me and you
	
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

	Player player;

	allLevels[0].setLevelAtDirection(&allLevels[1], Direction::Top);
	allLevels[0].setLevelAtDirection(&allLevels[2], Direction::Left);
	allLevels[0].setLevelAtDirection(&allLevels[3], Direction::Right);
	allLevels[0].setLevelAtDirection(&allLevels[4], Direction::Bot);

	allLevels[1].setLevelAtDirection(&allLevels[0], Direction::Bot);
	allLevels[2].setLevelAtDirection(&allLevels[0], Direction::Right);
	allLevels[3].setLevelAtDirection(&allLevels[0], Direction::Left);
	allLevels[4].setLevelAtDirection(&allLevels[0], Direction::Top);

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

