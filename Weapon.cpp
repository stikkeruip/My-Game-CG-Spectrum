#include "Weapon.h"
#include "Player.h"

void Weapon::InteractWith(Player* player)
{
	player->setWeapon(this);
	displayCharacter = ' ';
}
