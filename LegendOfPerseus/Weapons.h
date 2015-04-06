#pragma once
#include "gameobject.h"
#include <SFML/System/Vector2.hpp>
class Weapons :
	public GameObject
{
public:
	virtual void Update(void) = 0; //Main update for weapons
	virtual void Update(sf::Vector2f player) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0; //Draws the weapon
	virtual sf::Vector2f getPosition() = 0; //Returns the position of the weapon
	virtual float getHeight() = 0; //Returns the height
	virtual float getWidth() = 0; //Returns the width
	virtual void hitMonster() = 0;
	virtual void playSound() = 0;
	bool active; //Boolean if the weapon is still active
	int damage; //The amount of damage a weapon does
};