#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class Menu
{
public:
	Menu(void);
	void Draw(sf::RenderWindow &windows);
	void showMenu(sf::RenderWindow &windows);
	void showGameOver(sf::RenderWindow &windows, int score);
	void showVictory(sf::RenderWindow &windows, int score);
	bool getGameOver(void);
	bool getVictory(void);
	void setGameOver(bool gameOver);
	void setVictory(bool victory);
	string toString(int points);
	~Menu(void);
private:
	sf::Texture titleScreenImage;
	sf::Sprite menuImage;
	sf::Text text;
	sf::Font font; //font that displays score
	bool isplaying;
	bool gameOver;
	bool victory;
	int score;
};

