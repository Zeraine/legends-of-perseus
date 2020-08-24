#include "stdafx.h"
#include "Spear.h"
#include <iostream>


Spear::Spear(sf::Vector2f position)
{
	active = true;
	damage = 1;
	//Load Texture
	if (!texture.loadFromFile("Images/spear.png"))
	{
		std::cout << "Failed to Load Spear";
	} else {
		sprite.setTexture(texture);
		//sprite.setScale(sf::Vector2f(1.7f, 1.7f)); // absolute scale factor
	}
	sprite.setPosition(position); //Sets the position of the spear
	buffer.loadFromFile("Audio/hit.ogg");
	sound.setBuffer(buffer);
	sound.setVolume(70.0f);
}


Spear::~Spear(void)
{
}

void Spear::Update(void){
	/*sf::Vector2f position = sprite.getPosition();
	position.x += 18;
	sprite.setPosition(position);
	if (position.x > screenWidth) {
		//Set to not visible so it can be delete
		active = false;
	}*/
}

void Spear::Update(sf::Vector2f player){
	sf::Vector2f position = sprite.getPosition();
	position.x += 18;
	sprite.setPosition(position);
	if (position.x > screenWidth) {
		//Set to not visible so it can be delete
		active = false;
	}
}

void Spear::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

sf::Vector2f Spear::getPosition(){
	return sprite.getPosition();
}

float Spear::getHeight(){
	return sprite.getGlobalBounds().height;
}

float Spear::getWidth() {
	return sprite.getGlobalBounds().width;
}

void Spear::hitMonster() {
	active = false;
}

void Spear::playSound(){
	sound.play();
}

