#pragma once
#include "gameobject.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Weapons.h"
#include "Monster.h"
#include "Spear.h"
#include "Sword.h"
#include "ReflectedProjectile.h"

class Perseus : public GameObject
{
public:
	Perseus(void);
	~Perseus(void);
	bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;
	sf::Vector2<float> getLocation();
	void Draw(sf::RenderWindow &window);
	void Update(void);
	void reflect(Monster* monster); //If projectiles hit the shield, reflect them
	std::vector<Weapons*> getWeapons(void);
	bool checkCollision(Monster *monster);
	bool isAlive;
	void hurt();
	int health;
	int shieldTimer; //Shields power bar
	const int shieldTimerMax; //How long the shield can last, bar should be scaled to this value
	bool isUsingShield; //Are we using the shield
	bool isInvincible; //Do we still have invincibility frames
	void cleanWeapons();
private:
	void throwSpear();
	void swingSword();
	void useShield();
	void recoverShield();
	std::vector<Weapons*> weapons;
	int spearOffsetY;
	int weaponTimer;
	int shieldDecayRate; //How fast the shield bar depletes
	int shieldRecoveryRate; //How fast the shield bar regenerates.
	bool canUseShield; //Can we use the shield
	int invincibilityFrames;
	int invincibilityTimer;
	//1 for Spear, 2 for Sword, 3 for Shield
	int weaponUsed;
	float moveSpeed;
	int spearSpeed; //How fast can Perseus attack with the spear
	int swordSpeed; //How fast can Perseus attack with the sword
	sf::Sprite bodySprite;
	sf::Texture bodyTexture;
	sf::Sprite wingSprite;
	sf::Texture wingTexture;
	sf::Sprite shieldSprite;
	sf::Texture shieldTexture;
	int counter;
	int wingFrame;
	int shieldFrame;
};

