#include <conio.h>
#include <iostream>
#include "Player.h"
#include "Level.h"
#include "Weapon.h"

Player::Player() : Entity(11, 12)
{
	currentRoom = 0;
	displayCharacter = '@';
	direction = Direction::None;
	attackDir = Direction::None;

	playerHasKey = false;
	enteredPassway = false;
	hasAttacked = false;
	teleported = false;

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

int Player::attack(Direction direction)
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

void Player::movement()
{
	int index = currentRoom->GetIndexFromCoordinates(x, y);

	if (currentRoom->getContentAt(index) == ' ')
	{
		setX(x);
		setY(y);
	}
	else if (currentRoom->getContentAt(index) == '*')
	{
		setPlayerHasKey(true);
		currentRoom->setContentAt(index, ' ');
		setX(x);
		setY(y);
	}
	else if (currentRoom->getContentAt(index) == 'D' && getPlayerHasKey())
	{
		setPlayerHasKey(false);
		currentRoom->setContentAt(index, ' ');
		setX(x);
		setY(y);
	}
	else if (currentRoom->getContentAt(index) == 'X')
	{
		currentRoom->setContentAt(index, ' ');
		setX(x);
		setY(y);
		reachedEnd = true;
		return;
	}
	else if (currentRoom->getItemAt(index))
	{
		Object* item = currentRoom->getItemAt(index);
		if (item->IsWalkable())
		{
			setX(x);
			setY(y);
		}
		item->InteractWith();
		if (item->IsPickable())
		{
			currentRoom->clearItemAt(index);
		}
	}
}
