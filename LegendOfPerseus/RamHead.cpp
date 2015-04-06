#include "stdafx.h"
#include "RamHead.h"

RamHead::RamHead(float x, float y)
{
	hp = 5;
	points = 1000;
	width = 159;
	height = 199;
	position = sf::Vector2f(x, y);
	velocity = sf::Vector2f(0.0f, 0.0f);
	//Load Texture
	if (!texture.loadFromFile("chimera_ramhead.png"))
	{
		std::cout << "Failed to Load image";
	} else {
		sprite.setTexture(texture);
	}
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	sprite.setPosition(position);
	killed = false;
	isAlive = true;
	fireballtimer = 0;
}

RamHead::~RamHead(void)
{
}

bool RamHead::hitPerseus(bool shieldIsUsed, bool &reflected)
{
	//Bosses don't die when hit by perseus
	return true; //damage perseus
}

int RamHead::getPoints() {
	return points; //Returns points
}
bool RamHead::getKilled(){
	return killed; //Returns if killed
}
std::vector<Monster*> RamHead::Update(sf::Vector2f player){
	std::vector<Monster*> fireballs;
	sf::Vector2f position = getPosition(); //Position of the monster
	position.y += 100;
	position.x += 5;
	if (fireballtimer == 80) {
		//Fireball 1
		Fireball* fireball1 = new Fireball(position); //Shoot a fireball
		fireballs.push_back(fireball1);

		//Fireball 2
		Fireball* fireball2 = new Fireball(position, sf::Vector2f(0.6f, 0.6f));//Shoot a fireball
		fireball2->setColor(sf::Color::Red);
		fireballs.push_back(fireball2);
		
		//Fireball 3
		Fireball* fireball3 = new Fireball(position, sf::Vector2f(0.6f, -0.6f));//Shoot a fireball
		fireball3->setColor(sf::Color::Red);
		fireballs.push_back(fireball3); //Puts it the vector
		fireballtimer = 0; //Resets the timer
	}
	else {
		fireballtimer++;
	}

	updatePosition();
	return fireballs; //Returns the vector of fireballs
}