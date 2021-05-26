#include "Portal.h"

void Portal::InteractWith(Player* player)
{
	if (targetPortal)
	{
		player->setPlayerX(targetPortal->x);
		player->setPlayerY(targetPortal->y);
	}
}
