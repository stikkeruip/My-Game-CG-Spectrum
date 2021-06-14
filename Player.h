#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

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

class Player
{
	private:
		Level* currentRoom;
		int playerX;
		int playerY;
		int prevX;
		int prevY;
		Direction direction;
		Direction attackDir;
		

		bool playerHasKey;
		bool enteredPassway;
		bool hasAttacked;
		bool teleported;

		Weapon* weapon;
		Entity* entity;

	public:
		Player();

	
		//setters
		void setCurrentRoom(Level* _currentRoom) { currentRoom = _currentRoom; }

		void setEnteredPassway(bool x);

		void setWeapon(Weapon* x);

		void setHasAttacked(bool attacked) { hasAttacked = attacked; };

		void setAttackDir(Direction direction) { attackDir = direction; }

		void setPlayerX(int x) { playerX = x; }

		void setPlayerY(int y) { playerY = y; }

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

		int getPlayerX() { return playerX; };

		int getPlayerY() { return playerY; };

		bool getPlayerHasKey() { return playerHasKey; }

		void GetPositionAtDirection(Direction direction, int& x, int& y);

		int attack(Direction direction);

		int hit();

		bool getTeleported() { return teleported; }

};

#endif