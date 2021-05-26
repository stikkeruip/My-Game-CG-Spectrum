#include "Weapon.h"
#include "Player.h"

Weapon::Weapon(char c):LevelItem(c)
{
	walkable = true;
	pickable = true;
	damage = 10;
}

void Weapon::InteractWith(Player* player)
{
	player->setWeapon(this);
}
