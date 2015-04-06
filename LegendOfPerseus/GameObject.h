#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	virtual void Draw(sf::RenderWindow &window) = 0;
	virtual void Update(void) = 0;
	static int screenHeight;
	static int screenWidth;
};