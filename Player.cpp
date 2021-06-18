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
