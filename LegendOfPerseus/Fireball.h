#pragma once
#include "gameobject.h"
#include "Monster.h"

class Fireball :
	public Monster
{
public:
	Fireball(sf::Vector2f origin); //Constructor
	Fireball(sf::Vector2f origin, sf::Vector2f speedRatio);
	~Fireball(void); //Destructor
	void checkHits(std::vector<Weapons*> weapons); //To make sure that fireballs don't get hit by weapons
	int getPoints(); //Returns 0 (Fireball has no points
	//React when hit by perseus, return true if we damage perseus, set reflected to true if we are reflected
	bool hitPerseus(bool shieldIsUsed, bool &reflected);
	bool getKilled(); //Returns not true (Fireball can't be killed by perseus)
	void Update(void); //Empty function
	std::vector<Monster*> Update(sf::Vector2f); //Updates the position of the fireball
	void Draw(sf::RenderWindow& window); //Draws the fireball
	void setColor(sf::Color newColor);
private:
	int type; //Different types of fireballs (0 = Straight) (1 = Shoot at Location) (2 = shoot up) (3 = shoot down)
	sf::Vector2f speedRatio;
	int speed;
};