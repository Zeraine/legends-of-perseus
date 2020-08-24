#include "stdafx.h"
#include "Chimera.h"


Chimera::Chimera(float x, float y)
{
	bossspawn = false;
	position = sf::Vector2f(x, y);
	points = 2000;
	int width = 265;
	int height = 195;
	isAlive = true;
	if (!texture.loadFromFile("Images/chimera_body.png"))
	{
	std::cout << "Failed to Load image";
	} else {
	sprite.setTexture(texture);
	}
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	sprite.setPosition(position);

}

bool Chimera::hitPerseus(bool shieldIsUsed, bool &reflected)
{
	//Bosses don't die when hit by perseus
	return true; //damage perseus
}
int Chimera::getPoints()
{
	return points;
}
bool Chimera::getKilled()
{
	return killed;
}
void Chimera::checkHits(std::vector<Weapons*> weapons)
{
	for (unsigned int i=0; i<Chimheads.size(); i++){
		Chimheads[i]->checkHits(weapons);
	}
}
std::vector<Monster*> Chimera::Update(sf::Vector2f player)
{
	std::vector<Monster*> fireballs;
	if (position.x >= (screenWidth - 250)){velocity.x = -2;}
	else
	{
		velocity.x = 0;
		if (!bossspawn)
		{
			bossspawn = true;
			LionHead* lion = new LionHead(position.x-38, position.y-39);
			Chimheads.push_back(lion);
			SnakeHead* snake = new SnakeHead(position.x+130, position.y-164);
			Chimheads.push_back(snake);
			RamHead* ram = new RamHead(position.x+100, position.y-130);
			Chimheads.push_back(ram);
		}
	}

	for (unsigned int i=0; i<Chimheads.size(); i++){
		vector<Monster*> newProjectiles = Chimheads[i]->Update(player);
			for (unsigned int j=0;j<newProjectiles.size();j++){
				fireballs.push_back(newProjectiles[j]);
			}
	}

	for (unsigned int i=0;i<Chimheads.size();i++) {
			if (!Chimheads[i]->isAlive) {
				Monster* tempMonster = Chimheads[i];
				//hud.setScore(tempMonster->getPoints());
				Chimheads.erase(Chimheads.begin() + i);
				delete tempMonster;
				i--;
			}
		}

	if (Chimheads.size() == 0 && bossspawn)
	{
		isAlive = false;
		killed = true;
	}
	updatePosition();
	return fireballs;
}

void Chimera::Draw(sf::RenderWindow& window){
	window.draw(sprite); //Draws monster
	for (unsigned int i=0;i<Chimheads.size();i++) {
		Chimheads[i]->Draw(window);
	}
}

Chimera::~Chimera(void)
{
}
