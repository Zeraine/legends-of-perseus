#pragma once
#include "monster.h"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <math.h>

class MedusaHead :
	public Monster
{
public:
	MedusaHead(float x, float y); //Constructor
	~MedusaHead(void); //Destructor
	int getPoints(); //Returns the monster's points
	bool getKilled(); //Returns if the monster is killed by perseus or not
	//React when hit by perseus, return true if we damage perseus, set reflected to true if we are reflected
	bool hitPerseus(bool shieldIsUsed, bool &reflected);
	std::vector<Monster*> Update(sf::Vector2f); //Updates the position of the monster
	
private:
	float middle; //The center position of the monster
	float coscurve; //The curve the monster travels along
	float amplitude; //The amplitude of the wave
};

