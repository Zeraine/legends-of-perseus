#include "stdafx.h"
#include "Fireball.h"
#include <iostream>
using namespace std;

Fireball::Fireball(sf::Vector2f origin)
{
	position = origin;
	velocity = sf::Vector2f(0.0f, 0.0f);
	//Load Texture
	if (!texture.loadFromFile("fireball.png"))
	{
		std::cout << "Failed to Load image";
	} else {
		sprite.setTexture(texture);
	}
	sprite.setPosition(position);
	isAlive = true; //Sets the fireball to be alive
	hp = 1; //Give it HP
	points = 0; //Gives no points
	killed = false; //Is alive

	speed = 10;
	speedRatio = sf::Vector2f(1.0f,0.0f);
}

Fireball::Fireball(sf::Vector2f origin, sf::Vector2f initialSpeed) //overloaded for chimera boss
{
	position = origin;
	velocity = sf::Vector2f(0.0f, 0.0f);
	//Load Texture
	if (!texture.loadFromFile("fireball.png"))
	{
		std::cout << "Failed to Load image";
	} else {
		sprite.setTexture(texture);
	}
	sprite.setPosition(position);
	isAlive = true; //Sets the fireball to be alive
	hp = 1; //Give it HP
	points = 0; //Gives no points
	killed = false; //Is alive

	type = 1; //1 = shoot at Location
	speed = 8;
	speedRatio = initialSpeed;
}

Fireball::~Fireball(void)
{
}

bool Fireball::hitPerseus(bool shieldIsUsed, bool &reflected)
{
	isAlive = false; //no matter what happens, we die
	//Should only reflect if the shield is in use
	if(shieldIsUsed && getPosition().x) {
		reflected = true; //tell the game that the projectile got reflected
		return false; //successfully reflected, do not get hurt, do something and make it so we reflect
	}
	else {
		return true; //you done gouf'd and got hit anyway
	}
}

void Fireball::Update(void){
}

std::vector<Monster*> Fireball::Update(sf::Vector2f player){ //KEVINNNN!!!!!!!
	//Update Position
	sf::Vector2f position = getPosition();
	velocity.x = -speed * speedRatio.x;
	velocity.y = -speed * speedRatio.y;
	
	if (position.x < 0) {
		//Set to not visible so it can be deleted if it moves out of the screen
		isAlive = false;
	}
	if (position.y < 0){
		isAlive = false;
	}
	if (position.y > screenHeight){
		isAlive = false;
	}

	std::vector<Monster*> empty; //Empty vector to return

	updatePosition();
	return empty; //Returns the empty vector
}

void Fireball::Draw(sf::RenderWindow& window) {
	window.draw(sprite); //Draws the monster
}

void Fireball::checkHits(std::vector<Weapons*> weapons) {
	//Empty to make sure fireballs are not hit by weapons
}

int Fireball::getPoints() {
	return points; //Returns 0
}
bool Fireball::getKilled() {
	return false; //Returns false
}

void Fireball::setColor(sf::Color newColor) {
	sprite.setColor(newColor);
}