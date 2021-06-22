#pragma once

class Player;
class Level;

class Object
{
protected:
	
	Level* currentRoom;
	char displayCharacter;
	bool walkable;
	bool pickable;
	int x;
	int y;
	int id = 0;

public:
	
	Object(char c) : displayCharacter(c)
	{ 
		currentRoom = 0;
		pickable = false;
		walkable = false;
		x = -1;
		y = -1;
	}
	Object(int _x, int _y) : displayCharacter('0'), x(_x), y(_y)
	{
		currentRoom = 0;
		pickable = false;
		walkable = false;
	}
	
	virtual bool IsPickable() { return pickable; }
	virtual bool IsWalkable() { return walkable; }
	virtual void InteractWith(Player* player) {}
	

	//getters
	virtual int getID() { return id; }
	virtual int getX() { return x; }
	virtual int getY() { return y; }
	virtual char GetDisplayCharacter() { return displayCharacter; }
	Level* getCurrentRoom() { return currentRoom; }

	//setters
	virtual void setID(int x) { id = x; }
	virtual void setDisplayCharacter(char d) { displayCharacter = d; }
	virtual void setX(int x) { this->x = x; }
	virtual void setY(int y) { this->y = y; }
	void setCurrentRoom(Level* _currentRoom) { currentRoom = _currentRoom; }
};

