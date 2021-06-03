#pragma once
#ifndef WEAPON_H
#define WEAPON_H
#include "LevelItem.h"

class Weapon :
	public LevelItem
{
	protected:
		int damage;

	public:
		Weapon(int _x, int _y) :LevelItem(_x, _y)
		{
			displayCharacter = 'W';
			walkable = true;
			pickable = true;
			damage = 10;
		}

		//getters
		int getDamage() { return damage; };
		virtual void InteractWith( Player* player );
};
#endif
