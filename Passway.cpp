#include "Passway.h"

void Passway::InteractWith(Player* player)
{
	player->setEnteredPassway(true);
	player->setDirection(passwayDirection);
	player->setPlayerX(targetX);
	player->setPlayerY(targetY);
}
