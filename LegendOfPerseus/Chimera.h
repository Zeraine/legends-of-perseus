#pragma once
#include "Monster.h"
#include <vector>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
#include "LionHead.h"
#include "SnakeHead.h"
#include "RamHead.h"
#include <SFML/Audio.hpp>

class Chimera :
	public Monster
{
public:
	Chimera(float x, float y);
	~Chimera(void);
	bool hitPerseus(bool shieldIsUsed, bool &reflected);
	int getPoints();
	bool getKilled();
	virtual std::vector<Monster*> Update(sf::Vector2f);
	void checkHits(std::vector<Weapons*> weapons);
	void Draw(sf::RenderWindow& window);
	
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::vector<Monster*> Chimheads;
	bool bossspawn; //returns true if chimheads have already been loaded
};

