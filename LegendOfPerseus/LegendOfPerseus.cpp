// LegendOfPerseus.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "Perseus.h"
#include "Background.h"
#include "Hud.h"
#include "Menu.h"
#include "LevelLoader.h"
#include "TestMonster.h"
#include "HoverMonster.h"
#include "FollowMonster.h"
#include "MedusaHead.h"
#include <SFML/Audio.hpp>

#define SCREENSIZE_X 853
#define SCREENSIZE_Y 480

using namespace std;

void startLevel(string levelFileName, sf::RenderWindow &window, Menu menu) {
	
	//Object Initialization
	vector<GameObject*> objects;
	vector<Monster*> monsters;
	Perseus perseus;
	Background background;
	Hud hud;
	objects.push_back(&background);
	objects.push_back(&perseus);
	objects.push_back(&hud);
	int frame = 0;
	LevelLoader level(levelFileName);

	//Create transparent black rectangle to darken the screen when paused
	sf::RectangleShape pausescreendarken = sf::RectangleShape(sf::Vector2f(SCREENSIZE_X,SCREENSIZE_Y));
	pausescreendarken.setPosition(0.0f,0.0f);
	pausescreendarken.setFillColor(sf::Color(0,0,0,127));

	//Create "Paused" text to draw on top
	sf::Font font = sf::Font();
	font.loadFromFile("arcade.ttf");
	sf::Text pausescreentext = sf::Text();
	pausescreentext.setString("Paused");
	pausescreentext.setColor(sf::Color::White);
	pausescreentext.setFont(font);
	pausescreentext.setPosition (SCREENSIZE_X/2 - pausescreentext.getLocalBounds().width/2, 
								 SCREENSIZE_Y/2 - pausescreentext.getLocalBounds().height/2);

	bool levelCompleted = false;
	bool bossLoaded = false;
	bool gameOver = false;
	bool paused = false; //Dont start the game paused!
	sf::Music bgMusic;
	sf::Music boss;
	sf::Music victory;
	sf::Music gameover;
	if (!bgMusic.openFromFile("BGMusic.ogg")){
		cout << "Failed to Load Music";
	} else {
		bgMusic.setVolume(50);
		bgMusic.setLoop(true);
		bgMusic.play();
	}
	
	while (perseus.isAlive && window.isOpen() && !levelCompleted) {
		sf::Event event;
		//Game Loop
		//Wait for something to happen
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::KeyPressed:
					if(event.key.code == sf::Keyboard::P) {
						paused = !paused; //toggle pause state
						if(paused) { 
							window.draw(pausescreendarken); //draw pause effect to darken screen and draw "Paused" on the screen
							window.draw(pausescreentext);
							window.display();
						}
					}
					break;
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					if(paused) {
						window.draw(pausescreendarken); //draw pause effect to darken screen and draw "Paused" on the screen
						window.draw(pausescreentext);
						window.display();
					}
					break;

			}
		}

		if(paused) continue; //skip the rest of the loop if we are paused
		//If we are not paused, proceed to update the game state

		frame += 1; //increment the frame counter for the level

		//Clear Display
		window.clear(sf::Color(196,232,254,255));

		//Check for New Monsters
		vector<Monster*> newMonsters = level.checkForNewMonsters(frame);
		for (unsigned int i=0;i<newMonsters.size();i++) {
			monsters.push_back(newMonsters[i]);
		}

		//Update Objects
		for (unsigned int i=0;i<objects.size();i++) {
			objects[i]->Update();
		}

		//Update Shield Bar
		float shieldbarratio = (float)perseus.shieldTimer/(float)perseus.shieldTimerMax;
		hud.setShieldBar(shieldbarratio);

		//Update Monsters and see if they hit perseus
		for (unsigned int i=0;i<monsters.size();i++) {
			vector<Monster*> newProjectiles = monsters[i]->Update(perseus.getLocation());
			for (unsigned int j=0;j<newProjectiles.size();j++){
				monsters.push_back(newProjectiles[j]);
			}
			monsters[i]->checkHits(perseus.getWeapons());
			if (monsters[i]->getKilled() == true) //check to see if perseus actually killed the monster or not
				{
					hud.setScore(monsters[i]->getPoints());
				}
			//Check to see if Monster has hit perseus
			bool isHit = perseus.checkCollision(monsters[i]);
			if (isHit) {
				bool reflected = false; //reflected is set to true by hitPerseus if it the monster is reflected
				if(monsters[i]->hitPerseus(perseus.isUsingShield, reflected)) { //If we have hit perseus, the monster reacts
					//Damage perseus if hitPerseus returns true
					if (!perseus.isInvincible) {
						perseus.hurt();
						hud.setHealth(perseus.health); //update our health in case perseus was damaged
					}
				}
				else if(reflected) { //If the monster was reflectable, and was successfully reflected, reflect the monster
					perseus.reflect(monsters[i]);
				}
			}
		}

		//Draw Objects
		for (unsigned int i=0;i<objects.size();i++) {
			objects[i]->Draw(window);
		}

		//Draw Monsters
		for (unsigned int i=0;i<monsters.size();i++) {
			if (!monsters[i]->isAlive) {
				Monster* tempMonster = monsters[i];
				//hud.setScore(tempMonster->getPoints());
				monsters.erase(monsters.begin() + i);
				delete tempMonster;
				i--;
			} else {
				monsters[i]->Draw(window);
			}
		}
		if (monsters.size() == 0 && level.levelCompleted) {
			if (!bossLoaded) {
				bgMusic.stop();
				vector<Monster*> newMonsters = level.loadBoss();
				for (unsigned int j=0;j<newMonsters.size();j++){
					monsters.push_back(newMonsters[j]);
				}
				if (!boss.openFromFile("boss.ogg")){
					cout << "Failed to Load Music";
				} else {
					boss.setVolume(50);
					boss.setLoop(true);
					boss.play();
				}
				bossLoaded = true;
			} else {
				bgMusic.stop();
				boss.stop();
				levelCompleted = true;
				if (!victory.openFromFile("victory.ogg")){
					cout << "Failed to Load Music";
				} else {
					victory.setVolume(50);
					victory.setLoop(true);
					victory.play();
				}
				int score = hud.getScore();
				menu.showVictory(window, score);
				victory.stop();
			}
		}
		if (!(perseus.isAlive))
		{
			bgMusic.stop();
			boss.stop();
			if (!gameover.openFromFile("gameover.ogg")){
				cout << "Failed to Load Music";
			} else {
				gameover.setVolume(50);
				gameover.setLoop(true);
				gameover.play();
			}
			int score = hud.getScore();
			menu.showGameOver(window, score);
			gameover.stop();
		}
        window.display();
    }
	for (unsigned int i=0;i<monsters.size();i++){
		delete monsters[i];
	}
	perseus.cleanWeapons();
}

void startGame(sf::RenderWindow &window, Menu menu) {
	startLevel("Level1.txt", window, menu);
}

int _tmain(int argc, _TCHAR* argv[])
{
    //Intialize Window with Resolution and Disable Resizing via sf::Style::Close
	sf::RenderWindow window(sf::VideoMode(SCREENSIZE_X, SCREENSIZE_Y), "Legend of Perseus", sf::Style::Default);
	window.setFramerateLimit(60); // Set FPS limit to 60
	Menu menu = Menu();

	//Main Loop
    while (window.isOpen()) 
    {
		//Menu
		menu.showMenu(window);
		startGame(window, menu);
        window.display();
		
    }

    return 0;
}
