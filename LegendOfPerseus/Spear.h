#pragma once
#include "Weapons.h"
#include <SFML\System\Vector2.hpp>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>

class Spear :
	public Weapons
{
public:
	Spear(sf::Vector2f position);
	~Spear(void);
	void Update(void);
	void Update(sf::Vector2f player);
	void Draw(sf::RenderWindow& window);
	void playSound();
	sf::Vector2f getPosition();
	float getHeight();
	float getWidth();
	void hitMonster();
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

