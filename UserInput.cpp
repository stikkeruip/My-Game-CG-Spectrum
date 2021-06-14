#include "UserInput.h"
#include "Player.h"
#include <conio.h>



int UserInput::getch_noblock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

void UserInput::getInput()
{
	char input = getch_noblock();

	switch (input)
	{
	case 'w':
	case 'W':
	{
		Direction::Top;
		break;
	}
	case 's':
	case 'S':
	{
		Direction::Bot;
		break;
	}
	case 'a':
	case 'A':
	{
		Direction::Left;
		break;
	}
	case 'd':
	case 'D':
	{
		Direction::Right;
		break;
	}
}