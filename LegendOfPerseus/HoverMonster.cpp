#include "stdafx.h"
#include "HoverMonster.h"
#include <iostream>
using namespace std;

HoverMonster::HoverMonster(float x, float y)
{
	srand(time(NULL)); //Seed
	hp = 2; 
	points = 200;
	width = 48; //To be used for sprites
	height = 80;
	position = sf::Vector2f(x, y);
	velocity = sf::Vector2f(0.0f, 0.0f);

	//Load Texture
	if (!texture.loadFromFile("Images/harpy.png"))
	{
		std::cout << "Failed to Load image";
	} else {
		sprite.setTexture(texture);
	}
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	sprite.setPosition(position);

	//Load Wings Texture
	if (!wingTexture.loadFromFile("Images/harpy_wings.png"))
	{
		std::cout << "Couldn't load wings";
	} else {
		wingSprite.setTexture(wingTexture);
	}
	wingSprite.setTextureRect(sf::IntRect(0, 0, width, height));
	wingSprite.setPosition(position);

	isAlive = true;
	killed = false;
	vertical = true;
	fireballtimer = 0; //Shooting Timer
	counter = 0;
	wingFrame = 0;
}


HoverMonster::~HoverMonster(void)
{
}

bool HoverMonster::hitPerseus(bool shieldIsUsed, bool &reflected) {
	isAlive = false; //we die if we hit perseus
	return true; //damage perseus
}

void HoverMonster::Draw(sf::RenderWindow& window) {
	Monster::Draw(window);
	window.draw(wingSprite); //Draw wings
}

std::vector<Monster*> HoverMonster::Update(sf::Vector2f) {
	sf::Vector2f position = getPosition(); //Current position
	std::vector<Monster*> fireballs; //Vector of fireballs
	if (position.y < 0){vertical = false;} //Hit top of screen
	if ((position.y + getSize().y) > screenHeight){vertical = true;} //Hit bottom of screen
	if (position.x > (screenWidth - 100)){velocity.x = -5;} //Moves horizontally until it hits a certain part of the screen (Number can be changed)
	else {
		velocity.x = 0;
		if (vertical){velocity.y = -5;} //Moves up
		else {velocity.y = 5;} //Moves down
	}

	//Kill Monsters that move out of the screen
	if (position.x + getSize().x < 0) {
		isAlive = false;
	}

	if (position.x < screenWidth) {
		if (fireballtimer == 40) {
			Fireball* fireball = new Fireball(getPosition()); //Shoots a fireball
			fireballs.push_back(fireball); //Puts it the vector
			fireballtimer = 0; //Resets the timer
		}
		else{fireballtimer++;} //Increases the timer
	}

	switch(fireballtimer) {
		case 5:
			sprite.setTextureRect(sf::IntRect(0, 0, width, height));
			break;
		case 35:
			sprite.setTextureRect(sf::IntRect(48, 0, width, height));
			break;
	}

	//Rotate Frame on Wings
	counter += 1;
	if (counter == 10) {
		wingFrame += 1;
		counter = 0;
		if (wingFrame > 3) {
			wingFrame = 0;
		}

		sf::IntRect subRect;
		subRect.left = wingFrame*48;
		subRect.top = 0;
		subRect.width = 48;
		subRect.height = 80;
		wingSprite.setTextureRect(subRect);
	}

	//make sure we update our position from our velocity
	updatePosition();

	return fireballs; //Returns the vector of fireballs
}

void HoverMonster::Update(void){
}

void HoverMonster::updatePosition() {
	Monster::updatePosition();
	wingSprite.setPosition(position);
}

int HoverMonster::getPoints() {
	return points; //Returns points
}

bool HoverMonster::getKilled(){
	return killed; //Returns if killed
}

//Shrunken Hitbox Hack
sf::Vector2f HoverMonster::getSize() {
	return sf::Vector2f(sprite.getGlobalBounds().width-5, sprite.getGlobalBounds().height-5); //Returns size
}

//Shrunken Hitbox Hack
sf::Vector2f HoverMonster::getPosition() {
	sf::Vector2f hitBox = position;
	hitBox.x - 5;
	hitBox.y + 5;
	return hitBox;
}