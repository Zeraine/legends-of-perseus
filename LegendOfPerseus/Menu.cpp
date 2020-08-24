#include "stdafx.h"
#include "Menu.h"


Menu::Menu(void)
{
	titleScreenImage.loadFromFile("Images/TitleScreen.png"); // replace with actual background
	menuImage.setTexture(titleScreenImage);
	menuImage.setScale(1.0f, 1.0f);
	font.loadFromFile("Font/arcade.ttf");
	gameOver = false;
	victory = false;
}

Menu::~Menu(void)
{
}


void Menu::Draw(sf::RenderWindow &window)
{
	if (!(gameOver) && !(victory))
	{
		window.draw(menuImage);
		window.display();
	}
	else if (gameOver)
	{
		window.clear(sf::Color::Black);
		text.setPosition(350, 180);
		text.setFillColor(sf::Color::White);
		text.setFont(font);
		text.setString("   Game Over\n\n" + toString(score));
		window.draw(text);
		window.display();
	}
	else
	{
		window.clear(sf::Color::Black);
		text.setPosition(350, 180);
		text.setFillColor(sf::Color::White);
		text.setFont(font);
		text.setString("Congratulations!\nYou have defeated the chimera\nand saved your people\n\n" + toString(score));
		window.draw(text);
		window.display();
	}
}

void Menu::showMenu(sf::RenderWindow &window)
{
	bool showingMenu = true;
	sf::Event event;
	Draw(window);
	//Wait for something to happen
	while (showingMenu) {
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					showingMenu = false;
					break;
				case sf::Event::Resized:
					Draw(window);
					break;
			}
		}
	}

}
void Menu::showGameOver(sf::RenderWindow &window, int score)
{
	sf::Event event;
	gameOver = true;
	this->score = score;
	Draw(window);
	while (gameOver) {
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				gameOver = false;
				break;
			case sf::Event::Resized:
				Draw(window);
				break;
			}
		}
	}
}
void Menu::showVictory(sf::RenderWindow &window, int score)
{
	sf::Event event;
	victory = true;
	this->score = score;
	Draw(window);
	while (victory) {
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				victory = false;
				break;
			case sf::Event::Resized:
				Draw(window);
				break;
			}
		}
	}
}
bool Menu::getGameOver()
{
	return gameOver;
}

void Menu::setGameOver(bool gameOver)
{
	this->gameOver = gameOver;
}

string Menu::toString(int points)
{
	sf::String score = "Final Score\n" +std::to_string(static_cast<long long>(points));
	return score;
}