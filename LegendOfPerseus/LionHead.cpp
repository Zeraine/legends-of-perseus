#include "stdafx.h"
#include "LionHead.h"


LionHead::LionHead(float x, float y)
{
	hp = 10;
	points = 1000;
	width = 169;
	height = 195;
	position = sf::Vector2f(x, y);
	velocity = sf::Vector2f(0.0f, 0.0f);
	//Load Texture
	if (!texture.loadFromFile("Images/chimera_lionhead.png"))
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

bool LionHead::hitPerseus(bool shieldIsUsed, bool &reflected)
{
	//Bosses don't die when hit by perseus
	return true; //damage perseus
}

int LionHead::getPoints() {
	return points; //Returns points
}
bool LionHead::getKilled(){
	return killed; //Returns if killed
}
std::vector<Monster*> LionHead::Update(sf::Vector2f player){
	std::vector<Monster*> fireballs;

	if (fireballtimer == 60)
	{
		sf::Vector2f position = getPosition(); //Position of the monster
		sf::Vector2f fireballSpeedRatio;
		position.y += 80;
		position.x -= 3;
		float angle = atan2(position.x-player.x, position.y-player.y);
		fireballSpeedRatio.y = cos(angle);
		fireballSpeedRatio.x = sin(angle);

		//Make Fireball
		Fireball* fireball = new Fireball(position, fireballSpeedRatio); //Shoots a fireball
		fireballs.push_back(fireball); //Puts it the vector
		fireballtimer = 0; //Resets the timer
	}
	else
		{
			fireballtimer++;
		}

	updatePosition();

	return fireballs; //Returns the vector of fireballs
}

LionHead::~LionHead(void)
{
}
