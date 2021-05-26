#include "Button.h"
#include "Gate.h"

void Button::InteractWith(Player* player)
{
	if (gate)
	{
		displayCharacter = 'b';
		gate->Open();
	}
}
