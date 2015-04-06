#include "stdafx.h"
#include "Background.h"

using namespace std;

Background::Background(void)
{
	srand (time(NULL));
	backgroundimage.loadFromFile("Background.jpg"); //Loads the background image
	cloudimage.loadFromFile("Cloud.png"); //Loads the cloud image
	for (int i = 0; i < 2; i++)
	{
		background[i].setTexture(backgroundimage); //loads the background texture into the sprites
		cloud[i].setTexture(cloudimage);
		background[i].setScale(1.0f, 1.0f); //Sets the size of the sprites
		cloud[i].setScale(1.0f, 1.0f);
	}
	background[1].setPosition(float(background[0].getPosition().x + backgroundimage.getSize().x), 0); //Moves the second background to behind the first one
	cloud[1].setPosition(float(cloud[0].getPosition().x + cloudimage.getSize().x), 0);
}


Background::~Background(void)
{
}

void Background::Draw(sf::RenderWindow& window) {
	window.draw(background[0]);
	window.draw(background[1]);
	window.draw(cloud[0]);
	window.draw(cloud[1]);
}

void Background::Update(void) {
	sf::Vector2f bgOnePos = background[0].getPosition();
	sf::Vector2f bgTwoPos = background[1].getPosition();
	sf::Vector2f cloudOnePos = cloud[0].getPosition();
	sf::Vector2f cloudTwoPos = cloud[1].getPosition();
	background[0].setPosition(((bgOnePos.x)-0.1),bgOnePos.y); //Moves the background
	background[1].setPosition(((bgTwoPos.x)-0.1),bgTwoPos.y); //Moves the second background
	cloud[0].setPosition(((cloudOnePos.x)-1),cloudOnePos.y); //Moves the cloud
	cloud[1].setPosition(((cloudTwoPos.x)-1),cloudTwoPos.y); //Moves the cloud
	if ((background[0].getPosition().x + backgroundimage.getSize().x) < 0)
	{
		background[0].setPosition(float(background[1].getPosition().x + backgroundimage.getSize().x)-1, 0); //Moves the first background to behind the second one if it moves out of the screen
	}
	if ((background[1].getPosition().x + backgroundimage.getSize().x) < 0)
	{
		background[1].setPosition(float(background[0].getPosition().x + backgroundimage.getSize().x)-1, 0); //Moves the second background to behind the first one if it moves out of the screen
	}
	if ((cloud[0].getPosition().x + cloudimage.getSize().x) < 0)
	{
		cloud[0].setPosition(float(cloud[1].getPosition().x + cloudimage.getSize().x), 0); //Moves the first cloud to behind the second one if it moves out of the screen
	}
	if ((cloud[1].getPosition().x + cloudimage.getSize().x) < 0)
	{
		cloud[1].setPosition(float(cloud[0].getPosition().x + cloudimage.getSize().x), 0); //Moves the second cloud to behind the first one if it moves out of the screen
	}
}
