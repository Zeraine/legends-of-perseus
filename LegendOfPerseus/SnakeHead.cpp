#include "stdafx.h"
#include "SnakeHead.h"


SnakeHead::SnakeHead(float x, float y)
{
	hp = 10;
	points = 1000;
	width = 151;
	height = 84;
	position = sf::Vector2f(x, y);
	velocity = sf::Vector2f(0.0f, 0.0f);
	//Load Texture
	if (!texture.loadFromFile("chimera_snakehead.png"))
	{
		std::cout << "Failed to Load image";
	} else {
		sprite.setTexture(texture);
	}
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	sprite.setPosition(position);
	killed = false;
	isAlive = true;
	lazerTimer =0;
}

SnakeHead::~SnakeHead(void)
{
}

bool SnakeHead::hitPerseus(bool shieldIsUsed, bool &reflected)
{
	//Bosses don't die when hit by perseus
	return true; //damage perseus
}

int SnakeHead::getPoints() {
	return points; //Returns points
}
bool SnakeHead::getKilled(){
	return killed; //Returns if killed
}
std::vector<Monster*> SnakeHead::Update(sf::Vector2f player){
	sf::Vector2f position = getPosition(); //Position of the monster
	position.y += 20;
	if (lazerTimer == 150) {
		lazerTimer = 0;
	}
	if (lazerTimer == 0 ) {
		float angle = atan2(position.x-player.x, position.y-player.y);
		fireballSpeedRatio.y = cos(angle);
		fireballSpeedRatio.x = sin(angle);
	}
	std::vector<Monster*> fireballs;
	if (lazerTimer < 20){
		Fireball* fireball = new Fireball(position, fireballSpeedRatio); //Shoots a fireball
		fireball->setColor(sf::Color(0, 200, 0, 64));
		fireballs.push_back(fireball); //Puts it the vector
	}
	lazerTimer++;

	updatePosition();
	return fireballs; //Returns the vector of fireballs
}
