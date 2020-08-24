#include "stdafx.h"
#include "MedusaHead.h"
#include <iostream>

MedusaHead::MedusaHead(float x, float y)
{
	hp = 2;
	points = 200;
	position = sf::Vector2f(x, y);
	velocity = sf::Vector2f(0.0f, 0.0f);
	//Load Texture
	if (!texture.loadFromFile("Images/medusahead.png"))
	{
		std::cout << "Failed to Load image";
	} else {
		sprite.setTexture(texture);
	}
	sprite.setPosition(position);
	isAlive = true;
	killed = false;
	middle = getPosition().y; //Sets the starting y position of the monster
	coscurve = 0;
	amplitude = 5;
}


MedusaHead::~MedusaHead(void)
{
}

bool MedusaHead::hitPerseus(bool shieldIsUsed, bool &reflected)
{
	isAlive = false; //we die if we hit perseus
	return true; //damage perseus
}

int MedusaHead::getPoints() {
	return points; //Returns points
}
bool MedusaHead::getKilled() {
	return killed; //Returns if killed
}

std::vector<Monster*> MedusaHead::Update(sf::Vector2f player) {
	sf::Vector2f position = getPosition(); //Current position
	velocity.x = -4; //Moves horizontally
	velocity.y = cos(coscurve)*amplitude; //Moves vertically
	coscurve += 0.04f; //Updates curve

	//Kill Monsters that move out of the screen
	if (position.x + getSize().x < 0) {
		isAlive = false;
	}
	std::vector<Monster*> empty; //Empty vector

	updatePosition();
	return empty; //Returns empty vector
}