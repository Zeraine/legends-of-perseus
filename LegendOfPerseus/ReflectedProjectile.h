#pragma once
#include "Weapons.h"
#include <SFML\System\Vector2.hpp>

class ReflectedProjectile :
	public Weapons
{
public:
	ReflectedProjectile(sf::Sprite projectileSprite, sf::Vector2f projectileVelocity, sf::Texture projectileTexture);
	~ReflectedProjectile(void);
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
	sf::Vector2f velocity;
};
