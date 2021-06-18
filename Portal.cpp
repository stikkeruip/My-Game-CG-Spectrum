#include "Portal.h"
#include "Player.h"

void Portal::InteractWith(Player* player)
{
	if (targetPortal && !player->getTeleported())
	{
		player->setX(targetPortal->x);
		player->setY((targetPortal->y));
		player->changeTeleportState();
	}
}
