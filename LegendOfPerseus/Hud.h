#pragma once
#include "gameobject.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
class Hud : public GameObject
{
public:
	Hud(void);
	~Hud(void);
	int getHealth();
	int getScore();
	void setHealth(int health);
	void setScore(int score);
	void setShieldBar(float shieldratio);
	string static toString(int points);
	void Draw(sf::RenderWindow &windows);
	void Update(void);
private:
	int health;
	int points;
	float shieldratio;
	sf::RectangleShape shieldbarbackground;
	sf::RectangleShape shieldbar;
	sf::Texture life;
	sf::Text scoreText;
	sf::Font font; //font that displays score
	sf::Sprite heart; //object of the individual health
	sf::Sprite hearts[5]; //array that holds the health
};

