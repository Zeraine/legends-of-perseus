#pragma once
#include "monster.h"
#include <vector>
#include "Fireball.h"
#include "Perseus.h"
#include <stdlib.h>

class HoverMonster :
	public Monster
{
public:
	HoverMonster(float x, float y); //Constructor
	~HoverMonster(void); //Destructor
	int getPoints(); //Returns the monster's points
	bool getKilled(); //Returns if the monster is killed by perseus
	//React when hit by perseus, return true if we damage perseus, set reflected to true if we are reflected
	bool hitPerseus(bool shieldIsUsed, bool &reflected);
	void Draw(sf::RenderWindow &window); //Draws the monster
	void Update(void); //Empty function
	std::vector<Monster*> Update(sf::Vector2f); //Updates the monster's position
	void updatePosition(); //Override Monster's update to update the wings
	virtual sf::Vector2f getSize(); //Returns monster size
	virtual sf::Vector2f getPosition(); //Returns monster position
private:
	bool vertical; //To see if the monster is going up or down
	int fireballtimer; //Timer to shoot the fireball
	sf::Sprite wingSprite; //The harpy wings sprite
	sf::Texture wingTexture; //The wings texture
	int counter; //Timer for the wing animation
	int wingFrame; //What wing frame is displayed
};