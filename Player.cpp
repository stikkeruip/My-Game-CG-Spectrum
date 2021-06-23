#include <conio.h>
#include <iostream>
#include "Player.h"
#include "Level.h"
#include "Weapon.h"

Player::Player() : Entity(11, 12)
{
	displayCharacter = '@';
	direction = Direction::None;
	attackDir = Direction::None;

	playerHasKey = false;
	enteredPassway = false;
	hasAttacked = false;
	teleported = false;
	reachedEnd = false;

	weapon = nullptr;
}

void Player::setEnteredPassway(bool x)
{
	enteredPassway = x;
}

void Player::setWeapon(Weapon* w)
{
	if (weapon != nullptr)
	{
		delete weapon;
	}
	weapon = w;
}

int Player::attack(Direction::Direction direction)
{	
	int x = this->x;
	int y = this->y;

	GetPositionAtDirection(direction, x, y);
	return currentRoom->GetIndexFromCoordinates(x, y);
}

int Player::hit()
{
	return weapon->getDamage();
}

int Player::getch_noblock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

Direction::Direction Player::Input()
{
	char input = getch_noblock();

	switch (input)
	{
	case 'w':
	case 'W':
	{
		return Direction::Direction::Top;
	}
	case 's':
	case 'S':
	{
		return Direction::Direction::Bot;
	}
	case 'a':
	case 'A':
	{
		return Direction::Direction::Left;
	}
	case 'd':
	case 'D':
	{
		return Direction::Direction::Right;
	}
	default:
		return Direction::Direction::None;
	}
}

void Player::Update()
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
		if (teleported)
			changeTeleportState();

		setX(newX);
		setY(newY);
	}
	else if (currentRoom->getContentAt(index) == '*')
	{
		setPlayerHasKey(true);
		currentRoom->setContentAt(index, ' ');
		setX(newX);
		setY(newY);
	}
	else if (currentRoom->getContentAt(index) == 'D' && getPlayerHasKey())
	{
		setPlayerHasKey(false);
		currentRoom->setContentAt(index, ' ');
		setX(newX);
		setY(newY);
	}
	else if (currentRoom->getContentAt(index) == 'X')
	{
		currentRoom->setContentAt(index, ' ');
		setX(newX);
		setY(newY);
		reachedEnd = true;
		return;
	}
	else if (currentRoom->getItemAt(index))
	{
		Object* item = currentRoom->getItemAt(index);
		if (item->IsWalkable())
		{
			setX(newX);
			setY(newY);
		}

		item->InteractWith(this);
		if (item->IsPickable())
		{
			currentRoom->clearItemAt(index);
		}
	}
	Sleep(6);
}
