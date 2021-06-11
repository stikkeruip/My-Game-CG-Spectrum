#include "Weapon.h"
#include "player.h"

void Weapon::InteractWith(Player* player)
{
	player->setWeapon(this);
	displayCharacter = ' ';
}
