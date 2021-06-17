#include "Button.h"

void Button::InteractWith(Player* player)
{
	if (gate)
	{
		displayCharacter = 'b';
		gate->Open();
	}
}
