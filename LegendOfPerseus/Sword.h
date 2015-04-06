#pragma once
#include "Weapons.h"
#include <SFML\System\Vector2.hpp>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>

class Sword :
	public Weapons
{
public:
	Sword(sf::Vector2f position);
	~Sword(void);
	void Update(void);
	void Update(sf::Vector2f player);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	float getHeight();
	float getWidth();
	void hitMonster();
	void playSound();
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int timer;
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

