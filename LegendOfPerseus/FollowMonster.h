#pragma once
#include "monster.h"
#include <vector>
#include <SFML/System/Vector2.hpp>


class FollowMonster :
	public Monster
{
public:
	FollowMonster(float x, float y); //Constructor
	~FollowMonster(void); //Destructor
	int getPoints(); //Returns monster's points
	bool getKilled(); //Returns if the monster is killed by perseus
	//React when hit by perseus, return true if we damage perseus, set reflected to true if we are reflected
	bool hitPerseus(bool shieldIsUsed, bool &reflected);
	std::vector<Monster*> Update(sf::Vector2f); //Updates the monster's position

private:
	int speed;
};