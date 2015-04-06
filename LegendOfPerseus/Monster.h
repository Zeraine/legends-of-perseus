#pragma once
#include "gameobject.h"
#include "Weapons.h"
//#include "Perseus.h"
#include <vector>

class Monster: public GameObject{
public:
	virtual void checkHits(std::vector<Weapons*> weapons); //Checks if the monster is hit by weapons
	virtual bool hitPerseus(bool isShieldUsed, bool &reflected) = 0; //React when hit by perseus, return true if we damage perseus
	virtual void Update(void); //Empty function
	virtual std::vector<Monster*> Update(sf::Vector2f) = 0; //Main update function
	virtual sf::Vector2f getPosition(); //Returns monster position
	virtual sf::Vector2f getVelocity(); //Returns monster velocity
	virtual sf::Vector2f getSize(); //Returns monster size
	virtual sf::Sprite getSprite();
	virtual sf::Texture getTexture();
	virtual int getPoints() = 0; //Returns monster points
	virtual bool getKilled() = 0; //Returns if the monster is killed by perseus or not
	virtual void Draw(sf::RenderWindow& window);
	bool isAlive; //boolean to see if monster is alive or not
protected:
	int hp; //Monster health
	int damageTimer;
	float width; //width of the monster (To be used for sprites)
	float height; //Height of the monster (to be used for sprites)
	sf::Vector2f velocity; //Current velocity of the monster
	sf::Vector2f position; //Current position of the monster
	sf::Sprite sprite; //Sprite of the monster
	sf::Texture texture; //Texture for sprite, should load noimage.png if there is no sprite yet
	bool isVisible; //Bool for if the monster is still on the screen
	bool killed; //Bool for if the monster is killed by perseus or not
	int points; //Number of points a monster has
	virtual void updatePosition(); //Update the monster's position by adding velocity
};

