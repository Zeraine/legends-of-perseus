#include "stdafx.h"
#include "Sword.h"
#include <iostream>

Sword::Sword(sf::Vector2f position)
{
	timer = 15;
	active = true;
	damage = 2;
	//Load Texture
	if (!texture.loadFromFile("slash.png"))
	{
		std::cout << "Failed to Load Sword Slash";
	} else {
		sprite.setTexture(texture);
	}
	sprite.setPosition(position); //Sets the position of the slash
	buffer.loadFromFile("slash.ogg");
	sound.setBuffer(buffer);
	sound.setVolume(70.0f);
	sound.play();
}


Sword::~Sword(void)
{
}

void Sword::Update(void){
	/*if (timer == 0) {
		active = false;
	} else {
		timer--;
		float transparencyScale = 255.f * (float(timer) / 15.f);
		sprite.setColor(sf::Color(255, 255, 255, transparencyScale));
	}*/
}

void Sword::Update(sf::Vector2f player){
	if (timer == 0) {
		active = false;
	} else {
		timer--;
		float transparencyScale = 255.f * (float(timer) / 15.f);
		sprite.setColor(sf::Color(255, 255, 255, transparencyScale));
	}
	sprite.setPosition((float)player.x+25,(float)player.y-25);
}

void Sword::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

sf::Vector2f Sword::getPosition(){
	return sprite.getPosition();
}

float Sword::getHeight(){
	return sprite.getGlobalBounds().height;
}

float Sword::getWidth() {
	return sprite.getGlobalBounds().width;
}

void Sword::hitMonster() {
}

void Sword::playSound(){
}
