#include "stdafx.h"
#include "Monster.h"
#include <iostream>

using namespace std;

void Monster::checkHits(std::vector<Weapons*> weapons) {
	for (unsigned int i=0;i<weapons.size();i++) {
		//Check for Collisions
		if (weapons[i]->getPosition().y + weapons[i]->getHeight() > this->getPosition().y && weapons[i]->getPosition().y < this->getPosition().y + this->getSize().y) {
			if (weapons[i]->getPosition().x + weapons[i]->getWidth() > this->getPosition().x && weapons[i]->getPosition().x < this->getPosition().x + this->getSize().x) {
				weapons[i]->hitMonster(); //Tell weaponn is was hit, so spear can delete itself
				this->hp -= weapons[i]->damage; //Deals weapon damage
				damageTimer = 5;
				weapons[i]->playSound(); //Plays weapon hit sound
				if (this->hp <= 0) { //If monster no longer has HP
					this->isAlive = false; //Monster is no longer alive
					this->killed = true; //Monster is killed by perseus
				}
			}
		}
	}
}

sf::Vector2f Monster::getVelocity() {
	return velocity;
}

sf::Vector2f Monster::getPosition() {
	return position;
}

sf::Sprite Monster::getSprite() {
	return sprite;
}

sf::Texture Monster::getTexture() {
	return texture;
}

sf::Vector2f Monster::getSize() {
	return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height); //Returns size
}

void Monster::updatePosition() {
	position.x += velocity.x; //update x position with velocity
	position.y += velocity.y; //update y position with velocity
	sprite.setPosition(position); //Sets position of sprite
	if (damageTimer > 0) {
		damageTimer--;
	}
}

void Monster::Draw(sf::RenderWindow& window) {
	if (damageTimer>0) {
		sprite.setColor(sf::Color(255, 150, 150, 255));
	} else {
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	window.draw(sprite); //Draws monster
}

void Monster::Update() {
	
}