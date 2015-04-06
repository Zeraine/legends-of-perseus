#include "stdafx.h"
#include "FollowMonster.h"
#include <iostream>
#define pi 3.145826

FollowMonster::FollowMonster(float x, float y)
{
	hp = 3; //Sets health
	points = 300; //Sets points
	width = 50; //To be used for sprites
	height = 50; //To be used for sprites
	position = sf::Vector2f(x, y);
	velocity = sf::Vector2f(0.0f, 0.0f);
	//Load Texture
	if (!texture.loadFromFile("eyeball.png")) //TODO: do not I REPEAT DO NOT SHIP WITH noimage.png set as any texture
	{
		std::cout << "Failed to Load image";
	} else {
		sprite.setTexture(texture);
	}
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	sprite.setPosition(position);
	killed = false; //Not killed by perseus
	isAlive = true; //Make sure its alive to start
	speed = 3; //speed the monster moves, should be quite a little slower than perseus can dodge
}


FollowMonster::~FollowMonster(void)
{
}

bool FollowMonster::hitPerseus(bool shieldIsUsed, bool &reflected)
{
	isAlive = false; //we die if we hit perseus
	return true;
}

std::vector<Monster*> FollowMonster::Update(sf::Vector2f player){
	sf::Vector2f position = getPosition(); //Position of the monster
	if (position.x > (player.x + speed))
	{
		velocity.x = -speed;
	}
	else if (position.x < (player.x - speed))
	{
		velocity.x = speed;
	}
	else velocity.x = 0;
	if (position.y > (player.y + speed))
	{
		velocity.y = -speed;
	}
	else if (position.y < (player.y - speed))
	{
		velocity.y = speed;
	} 
	else velocity.y = 0;//To make the monster move towards the player

	//Rotate towards player
	float angle = atan2(position.x-player.x, position.y-player.y);
	sprite.setRotation(90-(angle*180)/pi);

	updatePosition();

	//Kill Monsters that move out of the screen
	if (position.x + getSize().x < 0) {
		isAlive = false;
	}
	std::vector<Monster*> empty; //Vector to return
	return empty; //Returns empty vector
}

int FollowMonster::getPoints() {
	return points; //Returns points
}
bool FollowMonster::getKilled() {
	return killed; //Returns if the monster is killed by perseus
}