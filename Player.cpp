#include <conio.h>
#include <iostream>
#include "player.h"
#include "level.h"
#include "Weapon.h"

Player::Player()
{
	currentRoom = 0;
	playerX = 11;
	playerY = 12;
	prevX = 0;
	prevY = 0;
	direction = Direction::None;
	attackDir = Direction::None;

	playerHasKey = false;
	enteredPassway = false;
	hasAttacked = false;

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

void Player::GetPositionAtDirection(Direction direction, int& x, int& y)
{
	switch (direction)
	{
	case Direction::Top:
		y -= 1;
		break;
	case Direction::Right:
		x += 1;
		break;
	case Direction::Bot:
		y += 1;
		break;
	case Direction::Left:
		x -= 1;
		break;
	}
}

int Player::attack(Direction direction)
{	
	int x = playerX;
	int y = playerY;

	GetPositionAtDirection(direction, x, y);
	return currentRoom->GetIndexFromCoordinates(x, y);
}

int Player::hit()
{
	return weapon->getDamage();
}
