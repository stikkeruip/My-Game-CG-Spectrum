#include "Entity.h"

vector<Entity*> Entity::entityList;

void Entity::isDead()
{
	if (health <= 0) displayCharacter = ' ';
	dead = true;
}

void Entity::movement()
{
	x = x;
	y = y;
}