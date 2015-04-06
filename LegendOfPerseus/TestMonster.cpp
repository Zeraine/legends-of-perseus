#include "stdafx.h"
#include "TestMonster.h"
#include <iostream>

TestMonster::TestMonster(float x, float y)
{
	hp = 2;
	points = 100;
	width = 48; //To be used for sprites
	height = 64;
	position = sf::Vector2f(x, y);
	velocity = sf::Vector2f(0.0f, 0.0f);
	//Load Texture
	if (!texture.loadFromFile("pillar.png")) //TODO: do not I REPEAT DO NOT SHIP WITH noimage.png set as any texture
	{
		std::cout << "Failed to Load image";
	} else {
		sprite.setTexture(texture);
	}
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	sprite.setPosition(position);
	killed = false;
	isAlive = true;
}


TestMonster::~TestMonster(void)
{
}

int TestMonster::getPoints() {
	return points; //Returns points
}
bool TestMonster::getKilled(){
	return killed; //Returns if killed
}

bool TestMonster::hitPerseus(bool shieldIsUsed, bool &reflected)
{
	isAlive = false; //we die if we hit perseus
	return true; //damage perseus
}

std::vector<Monster*> TestMonster::Update(sf::Vector2f) {
	sf::Vector2f position = getPosition(); //Current Position
	velocity.x = -5; //Moves horizontally

	switch(hp) {
		case 2:
			sprite.setTextureRect(sf::IntRect(0, 0, width, height));
			break;
		case 1:
			sprite.setTextureRect(sf::IntRect(48, 0, width, height));
			break;
	}

	if (position.x + getSize().x < 0) {
		isAlive = false; //Kills monster if moved off screen
	}
	std::vector<Monster*> empty; //Empty vector

	updatePosition();
	return empty; //Returns empty vector
}