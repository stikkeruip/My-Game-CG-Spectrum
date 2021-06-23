#include "BasicEnemy.h"
#include "Level.h"

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

	int index = currentRoom->GetIndexFromCoordinates(newX, newY);

	if (currentRoom->getContentAt(index) == ' ')
	{
		setX(newX);
		setY(newY);
	}
}