#include "Weapon.h"

void Weapon::InteractWith(Player* player)
{
	player->setWeapon(this);
	displayCharacter = ' ';
}
