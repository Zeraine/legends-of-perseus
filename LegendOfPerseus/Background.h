#pragma once
#include "gameobject.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>

class Background :
	public GameObject
{
public:
	Background(void); //Constructor
	~Background(void); //Destructor
	void Draw(sf::RenderWindow &window); //Draw backgrounds
	void Update(void); //Update movement of backgrounds
private:
	sf::Texture backgroundimage; //Actual image of background
	sf::Texture cloudimage; //"Layered" images
	sf::Sprite cloud[2]; //image to be drawn
	sf::Sprite background[2]; //Background to be drawn
};

