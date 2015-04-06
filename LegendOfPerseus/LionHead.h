#pragma once
#include "monster.h"
#include "Fireball.h"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
class LionHead :
	public Monster
{
public:

	LionHead(float x, float y);
	~LionHead(void);
	int getPoints();
	bool getKilled();
	//React when hit by perseus, return true if we damage perseus, set reflected to true if we are reflected
	bool hitPerseus(bool shieldIsUsed, bool &reflected);
	virtual std::vector<Monster*> Update(sf::Vector2f);

private:
	int fireballtimer;
};

