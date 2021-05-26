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
		Weapon(char c);

		//getters
		int getDamage() { return damage; };
		virtual void InteractWith( Player* player );
};
#endif
