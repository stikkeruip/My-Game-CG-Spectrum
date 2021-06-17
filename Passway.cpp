#include "Passway.h"

void Passway::InteractWith(Player* player)
{
	player->setEnteredPassway(true);
	player->setDirection(passwayDirection);
	player->setX(targetX);
	player->setY(targetY);
}
