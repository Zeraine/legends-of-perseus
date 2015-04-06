#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Monster.h"
#include "TestMonster.h"
#include "MedusaHead.h"
#include "HoverMonster.h"
#include "FollowMonster.h"
#include "LionHead.h"
#include "RamHead.h"
#include "SnakeHead.h"
#include "Chimera.h"
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
class LevelLoader
{
public:
	LevelLoader(std::string levelFileName);
	~LevelLoader(void);
	std::vector<Monster*> checkForNewMonsters(int currentFrame);
	bool levelCompleted;
	vector<Monster*> loadBoss();
private:
	std::vector< std::vector<std::string> > newMonstersVector;
	Monster* createMonster(std::vector<std::string> monsterString);
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

