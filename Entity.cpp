#include "Entity.h"

vector<Entity*> Entity::entityList;

void Entity::isDead()
{
	if (health <= 0)
	{
		setDisplayCharacter(' ');
		dead = true;
	}
}

/*void Entity::movement()
{
	x = x;
	y = y;
}*/

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