#include "Object.h"

Level* Object::currentRoom;

void Object::setCurrentRoom(Level* _currentRoom)
{
	currentRoom = _currentRoom;
}
Level* Object::getCurrentRoom()
{
	return currentRoom;
}