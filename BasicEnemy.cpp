#include "BasicEnemy.h"
#include "Level.h"
#include <iostream>

Direction::Direction BasicEnemy::Input()
{
	int dir = rand() % (3 - 0 + 1) + 0;
	if (dir == 0)
	{
		return Direction::Top;
	}
	else if (dir == 1)
	{
		return Direction::Right;
	}
	else if (dir == 2)
	{
		return Direction::Bot;
	}
	else if (dir == 3)
	{
		return Direction::Left;
	}
}

void BasicEnemy::Update()
{
	int newX;
	int newY;
	int attackX;
	int attackY;
	int delta = 30;

	mUpdateTimer += delta;
	if (mUpdateTimer > mUpdateInterval)
	{
		Direction::Direction input = Input();
		newX = x;
		newY = y;

		attackX = x;
		attackY = y;

		switch (input)
		{
		case Direction::Direction::Top:
		{
			newY--;
			break;
		}
		case Direction::Direction::Bot:
		{
			newY++;
			break;
		}
		case Direction::Direction::Left:
		{
			newX--;
			break;
		}
		case Direction::Direction::Right:
		{
			newX++;
			break;
		}
		}

		int newindex = currentRoom->GetIndexFromCoordinates(newX, newY);
		int oldindex = currentRoom->GetIndexFromCoordinates(x, y);

		if (currentRoom->getContentAt(newindex) == ' ' && !currentRoom->getEntityAt(newindex))
		{
			currentRoom->levelEntities[newindex] = currentRoom->levelEntities[oldindex];
			currentRoom->levelEntities[oldindex] = nullptr;
			setX(newX);
			setY(newY);
		}
		mUpdateTimer = 0;
	}
	std::cout << x << " " << y;
}