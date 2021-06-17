#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Entity.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Level;
class Weapon;
class Entity;

enum class Direction
{
	None = -1,
	Top,
	Right,
	Bot,
	Left,
	Number
};

class Player : 
	public Entity
{
	private:
		Level* currentRoom;
		Direction direction;
		Direction attackDir;
		
		bool playerHasKey;
		bool enteredPassway;
		bool hasAttacked;
		bool teleported;

		Weapon* weapon;

	public:
		Player();

	
		//setters
		void setCurrentRoom(Level* _currentRoom) { currentRoom = _currentRoom; }

		void setEnteredPassway(bool x);

		void setWeapon(Weapon* x);

		void setHasAttacked(bool attacked) { hasAttacked = attacked; };

		void setAttackDir(Direction direction) { attackDir = direction; }

		void setPlayerHasKey(bool hasKey) { playerHasKey = hasKey; }

		void setDirection(Direction _direction) { direction = _direction; }

		void changeTeleportState() { teleported = !teleported; }


		//getters
		Level* getCurrentRoom() { return currentRoom; };

		Direction getDirection() { return direction; };

		bool getEnteredPassway() { return enteredPassway; };

		bool hasWeapon() { return weapon != nullptr; };

		bool GetHasAttacked() { return hasAttacked; };

		Direction getAttackDir() { return attackDir; };

		bool getPlayerHasKey() { return playerHasKey; }

		int attack(Direction direction);

		int hit();

		bool getTeleported() { return teleported; }

		void movement();
};

#endif