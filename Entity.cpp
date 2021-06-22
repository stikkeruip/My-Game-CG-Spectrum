#include "Entity.h"

void Entity::isDead()
{
	if (health <= 0)
	{
		setDisplayCharacter(' ');
		dead = true;
	}
}

void Entity::GetPositionAtDirection(Direction::Direction direction, int& x, int& y)
{
	switch (direction)
	{
	case Direction::Top:
		y -= 1;
		break;
	case Direction::Right:
		x += 1;
		break;
	case Direction::Bot:
		y += 1;
		break;
	case Direction::Left:
		x -= 1;
		break;
	}
}