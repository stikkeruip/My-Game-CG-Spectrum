#include <iostream>
#include "Level.h"


constexpr char kPlayerSymbol = '@';

vector<Object*> Level::itemTargets;
	
Level::Level(string _levelName) : levelName(_levelName)
{
	height = 26;
	width = 22;
	level = loadLevel(_levelName);
	

	for (int i = 0; i < (int)Object::Direction::Number; i++)
	{
		levelAtDirections[i] = nullptr;
	}

	InitObjects();
	loadItems(_levelName);
}

void Level::setLevelAtDirection(Level* level, Object::Direction direction)
{
	levelAtDirections[(int)direction] = level;

	if (passwayAtDirections[(int)direction])
	{
		Object::Direction connectedPasswayDirection;
		int deltaX = 0;
		int deltaY = 0;
		switch (direction)
		{
		case Object::Direction::Top:
			connectedPasswayDirection = Object::Direction::Bot;
			deltaY -= 1;
			break;
		case Object::Direction::Right:
			connectedPasswayDirection = Object::Direction::Left;
			deltaX += 1;
			break;
		case Object::Direction::Bot:
			connectedPasswayDirection = Object::Direction::Top;
			deltaY += 1;
			break;
		case Object::Direction::Left:
			connectedPasswayDirection = Object::Direction::Right;
			deltaX -= 1;
			break;
		}
		Passway* targetPassway = level->passwayAtDirections[(int)connectedPasswayDirection];
		passwayAtDirections[(int)direction]->SetTarget(targetPassway->X + deltaX, targetPassway->Y + deltaY);
	}
}

void Level::clearItemAt(int index)
{
	level[index] = ' ';
	Objects[index] = nullptr;
	levelEntities[index] = nullptr;
}

void Level::InitObjects()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = GetIndexFromCoordinates(x, y);
			Objects[index] = nullptr;
			char levelChar = level[index];
			if  (levelChar == '<')
			{
				passwayAtDirections[(int)Object::Direction::Left] = new Passway(levelChar, Object::Direction::Left, x, y);
				Objects[index] = passwayAtDirections[(int)Object::Direction::Left];
			}
			else if (levelChar == '>')
			{
				passwayAtDirections[(int)Object::Direction::Right] = new Passway(levelChar, Object::Direction::Right, x, y);
				Objects[index] = passwayAtDirections[(int)Object::Direction::Right];
			}
			else if (levelChar == '^')
			{
				passwayAtDirections[(int)Object::Direction::Top] = new Passway(levelChar, Object::Direction::Top, x, y);
				Objects[index] = passwayAtDirections[(int)Object::Direction::Top];
			}
			else if (levelChar == 'v')
			{
				passwayAtDirections[(int)Object::Direction::Bot] = new Passway(levelChar, Object::Direction::Bot, x, y);
				Objects[index] = passwayAtDirections[(int)Object::Direction::Bot];
			}
		}
	}
}

void Level::DrawLevel(int playerX, int playerY)
{ 
	char* p = new char[kLevelWidth * kLevelHeight];

	//Render the base level to buffer p
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = GetIndexFromCoordinates(x, y);
			p[index] = level[index];
		}
	}

	//Render player/item/entity to buffer p
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = GetIndexFromCoordinates(x, y);
			
			if (playerX == x && playerY == y)
			{
				p[index] = kPlayerSymbol;
			}
			else if (Objects[index] != nullptr)
			{
				p[index] = Objects[index]->GetDisplayCharacter();
			}
			else if (levelEntities[index] != nullptr)
			{
				int entityX = levelEntities[index]->getX();
				int entityY = levelEntities[index]->getY();
				int entityIndex = GetIndexFromCoordinates(entityX, entityY);
				p[entityIndex] = levelEntities[index]->GetDisplayCharacter();
			}
		}
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = GetIndexFromCoordinates(x, y);
			cout << p[index];
		}
		cout << endl;
	}

	delete p;
}

void Level::setTargets()
{
	for (size_t i = 0; i < itemTargets.size(); i++)
	{
		Button* buttonPtr = dynamic_cast<Button*>(itemTargets[i]);
		Gate* gatePtr = dynamic_cast<Gate*>(itemTargets[i]);
		Portal* portalPtr = dynamic_cast<Portal*>(itemTargets[i]);

		if (buttonPtr)
		{
			Gate* gate = nullptr;
			Button* button = buttonPtr;

			for (size_t y = i + 1; y < itemTargets.size(); y++)
			{
				Gate* gatePtr = dynamic_cast<Gate*>(itemTargets[y]);
				if (button && gate && (button->getID() == gate->getID()))
				{
					i = y - 1;
					break;
				}
				else if (gatePtr)
					gate = gatePtr;
			}
			if (button && gate && (button->getID() == gate->getID()))
			{
				button->SetTargetGate(gate);
			}
		}
		else if (gatePtr)
		{
			Gate* gate = gatePtr;
			Button* button = nullptr;

			for (size_t y = i + 1; y < itemTargets.size(); y++)
			{
				Button* buttonPtr = dynamic_cast<Button*>(itemTargets[y]);
				if (button && gate && (button->getID() == gate->getID()))
				{
					i = y - 1;
					break;
				}
				else if(buttonPtr)
					button = buttonPtr;
			}
			if (button && gate && (button->getID() == gate->getID()))
			{
				button->SetTargetGate(gate);
			}
		}
		else if (portalPtr)
		{
			Portal* portal_0 = portalPtr;
			Portal* portal_1 = nullptr;

			for (size_t y = i + 1; y < itemTargets.size(); y++)
			{
				Portal* portalPtr = dynamic_cast<Portal*>(itemTargets[y]);
				if (portal_0 && portal_1 && (portal_0->getID() == portal_1->getID()))
				{
					i = y - 1;
					break;
				}
				else if(portalPtr)
					portal_1 = portalPtr;
			}

			if (portal_0 && portal_1 && (portal_0->getID() == portal_1->getID()))
			{
				portal_0->SetTarget(portal_1);
				portal_1->SetTarget(portal_0);
			}
		}
	}
}

void Level::loadItems(string levelName)
{
	ifstream fname(levelName);
	string temp;
	int x;
	int y;
	int id;

	while (fname >> temp && temp != "LEVEL")
	{
		if (temp == "PORTAL")
		{
			fname >> temp;
			id = stoi(temp);

			fname >> temp;
			x = stoi(temp);

			fname >> temp;
			y = stoi(temp);

			Objects[GetIndexFromCoordinates(x, y)] = new Portal(x, y);
			Objects[GetIndexFromCoordinates(x, y)]->setID(id);
			level[GetIndexFromCoordinates(x, y)] = Objects[GetIndexFromCoordinates(x, y)]->GetDisplayCharacter();
			itemTargets.push_back(Objects[GetIndexFromCoordinates(x, y)]);
		}
		else if (temp == "ENEMY")
		{
			fname >> temp;
			x = stoi(temp);

			fname >> temp;
			y = stoi(temp);

			levelEntities[GetIndexFromCoordinates(x, y)] = new BasicEnemy(x, y);
			Entity::entityList.push_back(levelEntities[GetIndexFromCoordinates(x, y)]);
		}
		else if (temp == "WEAPON")
		{
			fname >> temp;
			x = stoi(temp);

			fname >> temp;
			y = stoi(temp);

			Objects[GetIndexFromCoordinates(x, y)] = new Weapon(x, y);
			level[GetIndexFromCoordinates(x, y)] = Objects[GetIndexFromCoordinates(x, y)]->GetDisplayCharacter();
		}
		else if (temp == "BUTTON")
		{
			fname >> temp;
			id = stoi(temp);

			fname >> temp;
			x = stoi(temp);

			fname >> temp;
			y = stoi(temp);

			Objects[GetIndexFromCoordinates(x, y)] = new Button(x, y);
			Objects[GetIndexFromCoordinates(x, y)]->setID(id);
			level[GetIndexFromCoordinates(x, y)] = Objects[GetIndexFromCoordinates(x, y)]->GetDisplayCharacter();
			itemTargets.push_back(Objects[GetIndexFromCoordinates(x, y)]);
		}
		else if (temp == "BDOOR")
		{
			fname >> temp;
			id = stoi(temp);

			fname >> temp;
			x = stoi(temp);

			fname >> temp;
			y = stoi(temp);

			Objects[GetIndexFromCoordinates(x, y)] = new Gate(x, y);
			Objects[GetIndexFromCoordinates(x, y)]->setID(id);
			level[GetIndexFromCoordinates(x, y)] = Objects[GetIndexFromCoordinates(x, y)]->GetDisplayCharacter();
			itemTargets.push_back(Objects[GetIndexFromCoordinates(x, y)]);
		}
		else if (temp == "KDOOR")
		{
			fname >> temp;
			x = stoi(temp);

			fname >> temp;
			y = stoi(temp);

			level[GetIndexFromCoordinates(x, y)] = 'D';
		}
		else if (temp == "KEY")
		{
			fname >> temp;
			x = stoi(temp);

			fname >> temp;
			y = stoi(temp);

			level[GetIndexFromCoordinates(x, y)] = '*';
		}
		else if (temp == "END")
		{
			fname >> temp;
			x = stoi(temp);

			fname >> temp;
			y = stoi(temp);

			level[GetIndexFromCoordinates(x, y)] = 'X';
		}
	}
}

char* Level::loadLevel(string levelName)
{
	ifstream fname(levelName);
	string temp;
	string txtLevel;

	while (fname >> temp)
	{
		if (temp == "HEIGHT")
		{
			fname >> temp;
			height = stoi(temp);
		}
		else if (temp == "WIDTH")
		{
			fname >> temp;
			width = stoi(temp);
		}
		else if (temp == "LEVEL")
		{
			getline(fname, temp);

			for (int i = 0; i < height; i++)
			{
				std::getline(fname, temp);
				txtLevel += temp;
			}
			char* levelData = new char[txtLevel.size() + 2];
			strcpy_s(levelData, txtLevel.size() + 1, &txtLevel[0]);

			return levelData;
		}
	}

	
}
