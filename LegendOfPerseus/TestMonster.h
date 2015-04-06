#pragma once
#include "monster.h"
#include <vector>
class TestMonster :
	public Monster
{
public:
	TestMonster(float x, float y); //Constructor
	~TestMonster(void); //Destructor
	int getPoints(); //Returns the points of the monster
	bool getKilled(); //Returns if the monster is killed by perseus or not
	//React when hit by perseus, return true if we damage perseus, set reflected to true if we are reflected
	bool hitPerseus(bool shieldIsUsed, bool &reflected);
	std::vector<Monster*> Update(sf::Vector2f); //Updates the position of the monster
};

