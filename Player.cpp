#include <conio.h>
#include <iostream>
#include "Player.h"
#include "level.h"
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

void Player::strike(Direction::Direction direction)
{
	return;

	int attackX = x;
	int attackY = y;

	setHasAttacked(true);
	setAttackDir(direction);
	attack(direction);
	GetPositionAtDirection(direction, attackX, attackY);
	if (currentRoom->getEntityAt(attackX, attackY))
	{
		currentRoom->getEntityAt(attackX, attackY)->setHealth(hit());
		currentRoom->getEntityAt(attackX, attackY)->setDead();
	}
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

	case KEY_UP:
	{
		strike(Direction::Direction::Top);
		return Direction::Direction::None;
	}
	case KEY_DOWN:
	{
		strike(Direction::Direction::Bot);
		return Direction::Direction::None;
	}
	case KEY_LEFT:
	{
		strike(Direction::Direction::Left);
		return Direction::Direction::None;
	}
	case KEY_RIGHT:
	{
		strike(Direction::Direction::Right);
		return Direction::Direction::None;
	}
	default:
		return Direction::Direction::None;
}
}

void Player::Update()
{
	int newX;
	int newY;

	Direction::Direction input = Input();
	newX = x;
	newY = y;

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
		if (teleported)
			changeTeleportState();

		setX(newX);
		setY(newY);
	}
	else if (currentRoom->getContentAt(newindex) == '*')
	{
		setPlayerHasKey(true);
		currentRoom->setContentAt(newindex, ' ');
		setX(newX);
		setY(newY);
	}
	else if (currentRoom->getContentAt(newindex) == 'D' && getPlayerHasKey())
	{
		setPlayerHasKey(false);
		currentRoom->setContentAt(newindex, ' ');
		setX(newX);
		setY(newY);
	}
	else if (currentRoom->getContentAt(newindex) == 'X')
	{
		currentRoom->setContentAt(newindex, ' ');
		setX(newX);
		setY(newY);
		reachedEnd = true;
		return;
	}
	else if (currentRoom->getItemAt(newindex))
	{
		Object* item = currentRoom->getItemAt(newindex);
		if (item->IsWalkable())
		{
			setX(newX);
			setY(newY);
		}

		item->InteractWith(this);
		if (item->IsPickable())
		{
			currentRoom->clearItemAt(newindex);
		}
	}
}
