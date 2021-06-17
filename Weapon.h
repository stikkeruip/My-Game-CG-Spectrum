#pragma once
#ifndef WEAPON_H
#define WEAPON_H
#include "Object.h"

class Weapon :
	public Object
{
	protected:
		int damage;

	public:
		Weapon(int _x, int _y) :Object(_x, _y)
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
