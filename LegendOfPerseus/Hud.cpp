#include "stdafx.h"
#include "Hud.h"

using namespace std;
Hud::Hud(void)
{
	health = 3;
	points = 0;
	shieldratio = 1.00;
	life.loadFromFile("Images/heart.png");
	font.loadFromFile("Font/arcade.ttf");
	heart.setTexture(life);
	for (int i = 0; i <= 4; i++) //The max health you can get is 5
	{
		hearts[i].setTexture(life);
		hearts[i].setPosition((10 + i*40), 10);
		hearts[i].setScale(.1f, .1f);
	}
	scoreText.setPosition (750, 5);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setFont(font);
	shieldbarbackground = sf::RectangleShape(sf::Vector2f(100,10));
	shieldbarbackground.setFillColor(sf::Color(255,0,0));
	shieldbarbackground.setPosition(sf::Vector2f(13,45));
	shieldbarbackground.setOutlineThickness(1);
	shieldbarbackground.setOutlineColor(sf::Color(0,0,0));
	shieldbar = sf::RectangleShape(sf::Vector2f(100, 10));
	shieldbar.setFillColor(sf::Color(0, 0, 225));
	shieldbar.setPosition(sf::Vector2f(13, 45));
}
int Hud::getHealth()
{
	return health;
}
int Hud::getScore()
{
	return points;
}
void Hud::setHealth(int health)
{
	this->health = health;
}
void Hud::setScore(int score)
{
	points += score;
}
void Hud::setShieldBar(float shieldratio)
{
	this->shieldratio = shieldratio;
	shieldbar.setScale(shieldratio, 1.0);
}
string Hud::toString(int points)
{
	sf::String score = "Score\n " +std::to_string(static_cast<long long>(points));
	return score;
}


void Hud::Draw(sf::RenderWindow &windows)
{
	//Only the first i hearts will be drawns which will be his current health Up to a max of 5 can be drawn
	for (int i = 0; i < health; i++)
	{
		windows.draw(hearts[i]);
	}
	scoreText.setString(toString(points));
	windows.draw(scoreText);
	windows.draw(shieldbarbackground);
	windows.draw(shieldbar);
}
void Hud::Update(void)
{
}

Hud::~Hud(void)
{
}
