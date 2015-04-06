#include "stdafx.h"
#include "ReflectedProjectile.h"
#include <iostream>

ReflectedProjectile::ReflectedProjectile(sf::Sprite projectileSprite, sf::Vector2f projectileVelocity, sf::Texture projectileTexture)
{
	active = true;
	damage = 2; //deal bonus damage for reflecting projectiles?
	sprite = projectileSprite;
	texture = projectileTexture;
	sprite.setTexture(texture);
	velocity = projectileVelocity;
}


ReflectedProjectile::~ReflectedProjectile(void)
{
}

void ReflectedProjectile::Update(void){
	/*sf::Vector2f position = sprite.getPosition();
	position.x += velocity.x;
	position.y += velocity.y;
	sprite.setPosition(position);
	if (position.x > screenWidth) {
		//Set to not visible so it can be delete
		active = false;
	}*/
}

void ReflectedProjectile::Update(sf::Vector2f player){
	sf::Vector2f position = sprite.getPosition();
	position.x += velocity.x;
	position.y += velocity.y;
	sprite.setPosition(position);
	if (position.x > screenWidth) {
		//Set to not visible so it can be delete
		active = false;
	}
}

void ReflectedProjectile::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

sf::Vector2f ReflectedProjectile::getPosition(){
	return sprite.getPosition();
}

float ReflectedProjectile::getHeight(){
	return sprite.getGlobalBounds().height;
}

float ReflectedProjectile::getWidth() {
	return sprite.getGlobalBounds().width;
}

void ReflectedProjectile::hitMonster() {
	active = false;
}

void ReflectedProjectile::playSound(){
}

