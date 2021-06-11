#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <fstream>
#include "player.h"
#include "LevelItem.h"
#include "Passway.h"
#include "Portal.h"
#include "Portal.h"
#include "Button.h"
#include "Gate.h"
#include "Weapon.h"
#include "Entity.h"
#include "BasicEnemy.h"

using namespace std;

constexpr int kLevelWidth = 22;
constexpr int kLevelHeight = 26;

class Level
{
	private:
		int width;
		int height;
		string levelName;

		void InitLevelItems();
		Level* levelAtDirections[(int)Direction::Number];
		Passway* passwayAtDirections[(int)Direction::Number];

		static vector<LevelItem*> itemTargets;
	public:
		Level(string levelName);

		char* level;
		Entity* levelEntities[kLevelWidth * kLevelHeight];
		LevelItem* levelItems[kLevelWidth * kLevelHeight]; //levelItems is an array of pointers (each of them points to a LevelItem)
		
		//setters
		void setLevelAtDirection(Level* level, Direction direction);

		void setContentAt(int index, char content) { level[index] = content; }

		static void setTargets();

		void clearItemAt(int index);


		//getters
		Level* getLevelAtDirection(Direction direction) { return levelAtDirections[(int)direction]; }

		int GetIndexFromCoordinates(int x, int y) { return x + y * width; };

		int getWidth() { return width; };

		char getContentAt (int index) { return level[index]; }

		LevelItem* getItemAt (int index) { return levelItems[index]; }
		LevelItem* getItemAt (int x, int y) { int index = GetIndexFromCoordinates(x, y); return getItemAt(index); }
		Entity* getEntityAt(int index) { return levelEntities[index]; }
		Entity* getEntityAt(int x, int y) { int index = GetIndexFromCoordinates(x, y); return getEntityAt(index); }

		//other functions
		bool hasLevelAtDirection(Direction direction) { return levelAtDirections[(int)direction] != nullptr; }

		void DrawLevel(int playerX, int playerY);

		char* loadLevel(string levelName);

		void loadItems(string levelName);
};

#endif
