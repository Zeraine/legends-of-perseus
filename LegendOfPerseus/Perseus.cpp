#include "stdafx.h"
#include "Perseus.h"

using namespace std;

Perseus::Perseus(void) : shieldTimerMax(120)
{
	this->movingLeft = false;
	this->movingRight = false;
	this->movingUp = false;
	this->movingDown = false;
	spearOffsetY = 16; //Position offset for spears to spawn at
	weaponTimer = 0; //Tracks how long until we can use a weapon again
	shieldTimer = shieldTimerMax; //Set the bar to max initially
	shieldDecayRate = 2; //Shield can be used for a full second
	shieldRecoveryRate = 1; //Shield takes 2 full seconds to recover if used entirely
	canUseShield = true;
	isUsingShield = false;
	health = 3;

	weaponUsed = 0;
	isAlive = true;
	isInvincible = false;
	moveSpeed = 6;
	spearSpeed = 30; //Throw 2 spears per second
	swordSpeed = 30; //Swing Sword 2 times per second
	invincibilityFrames = 45;
	invincibilityTimer = 0;
	wingFrame = 0;
	shieldFrame = 0;
	counter = 0;

	//Load Body Texture
	if (!bodyTexture.loadFromFile("Images/perseus.png"))
	{
		//Error
	} else {
		bodySprite.setTexture(bodyTexture);
		bodySprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}

	//Load Wings Texture
	if (!wingTexture.loadFromFile("Images/wings.png"))
	{
		//Error
	} else {
		wingSprite.setTexture(wingTexture);
		wingSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}

	//Load Shield Texture
	if (!shieldTexture.loadFromFile("Images/shield.png"))
	{
		//Error
	} else {
		shieldSprite.setTexture(shieldTexture);
		shieldSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}

	sf::Vector2f position = bodySprite.getPosition();
	position.y = 155;
	position.x = 30;
	bodySprite.setPosition(position);
}


Perseus::~Perseus(void)
{
}

void Perseus::Draw(sf::RenderWindow& window) {
	//Draw Perseus
	if (invincibilityTimer > 0 && invincibilityTimer % 2 == 0) {
		
	} else {
		window.draw(bodySprite);
		window.draw(wingSprite);
	}
	if (isUsingShield) {
		window.draw(shieldSprite);
	}
	//Draw weapons
	for (unsigned int i=0;i<weapons.size();i++) {
		weapons[i]->Update(this->getLocation());
		if (weapons[i]->active) {
			weapons[i]->Draw(window);
		} else {
			//Weapon isn't active, delete it!
			Weapons* tempWeapon = weapons[i];
			delete tempWeapon;
			weapons.erase(weapons.begin() + i);
			i--;
		}
	}
}

void Perseus::Update(void) {

	//Handle Keyboard Input
	sf::Vector2f position = bodySprite.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (position.x > 0) {
			position.x -= moveSpeed;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (position.x + bodySprite.getGlobalBounds().width < screenWidth ) {
			position.x += moveSpeed;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (position.y > 0) {
			position.y -= moveSpeed;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (position.y + bodySprite.getGlobalBounds().height < screenHeight){
			position.y += moveSpeed;
		}
	}
	// when X is pressed and there is no cooldown left we can throw a spear, also shield must not be held
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && weaponTimer == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		throwSpear();
		weaponTimer = spearSpeed;
		//1 for Spear
		weaponUsed = 1;
	}
	// when Z is pressed and there is no cooldown left we can swing the sword, also shield must not be held
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && weaponTimer == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		swingSword();
		weaponTimer = swordSpeed;
		//2 for Sword
		weaponUsed = 2;
	}
	// when C is pressed, there is no cooldown left and the shield bar is full, start using the shield
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && weaponTimer == 0) {
		if(canUseShield) //can we use the shield?
			useShield(); //use the shield
		//3 for Shield
		weaponUsed = 3;
	}
	// when C is released, the shield recovers and cannot be used until the shield bar is full again
	else {
		if(weaponUsed == 3)
			canUseShield = false;
		isUsingShield = false;
	}

	if(!isUsingShield)
		recoverShield(); //recover shield bar

	//Update Sprite Positions
	wingSprite.setPosition(position);
	bodySprite.setPosition(position);
	shieldSprite.setPosition(position);

	switch (weaponUsed) {
	case 1: //using spear
		switch (weaponTimer) {
		case 10:
			bodySprite.setTextureRect(sf::IntRect(0,0,64,64));
			break;
		case 30:
			bodySprite.setTextureRect(sf::IntRect(64,0,64,64));
			break;
		case 20:
			bodySprite.setTextureRect(sf::IntRect(128,0,64,64));
			break;
		}
		break;
	case 2: //swinging sword
		switch (weaponTimer) {
		case 20:
			bodySprite.setTextureRect(sf::IntRect(192,0,64,64));
			break;
		case 30:
			bodySprite.setTextureRect(sf::IntRect(256,0,64,64));
			break;
		case 25:
			bodySprite.setTextureRect(sf::IntRect(320,0,64,64));
			break;
		}
		break;
	case 3: //shield is used
		if(isUsingShield) //If shield is in use display the shield
			bodySprite.setTextureRect(sf::IntRect(448,0,64,64));
		else //If it isnt, just make the motion of putting up the shield
			bodySprite.setTextureRect(sf::IntRect(384,0,64,64));
		break;
	}

	//Rotate Frame on Wings
	counter += 1;
	if (counter == 7) {
		wingFrame += 1;
		counter = 0;
		if (wingFrame > 3) {
			wingFrame = 0;
		}

		sf::IntRect subRect;
		subRect.left = wingFrame*64;
		subRect.top = 0;
		subRect.width = 64;
		subRect.height = 64;
		wingSprite.setTextureRect(subRect);
	}

	if (counter == 5) {
		shieldFrame += 1;
		if (shieldFrame > 3) {
			shieldFrame = 0;
		}

		sf::IntRect subRect;
		subRect.left = shieldFrame*64;
		subRect.top = 0;
		subRect.width = 64;
		subRect.height = 64;
		shieldSprite.setTextureRect(subRect);
	}

	//Update Timers
	if (weaponTimer > 0) {
		weaponTimer--;
	}
	if (invincibilityTimer > 0) {
		invincibilityTimer--;
		if (invincibilityTimer == 0) {
			isInvincible = false;
		}
	}
}

void Perseus::reflect(Monster* monster) {
	//hacky solution until I think of something better
	sf::Vector2f velocity = monster->getVelocity();
	velocity.x *= -1; //reflect in x
	ReflectedProjectile* projectile = new ReflectedProjectile(monster->getSprite(), velocity, monster->getTexture());
	weapons.push_back(projectile);
}

void Perseus::throwSpear() {
	//Create Spear at Perseus' Position
	sf::Vector2f newSpearPosition = bodySprite.getPosition();
	newSpearPosition.y += spearOffsetY;
	Spear* spear = new Spear(newSpearPosition);
	weapons.push_back(spear);
}

void Perseus::swingSword() {
	//Create Sword At Perseus' Location
	sf::Vector2f perseusPosition = sf::Vector2f(bodySprite.getPosition().x, bodySprite.getPosition().y);
	perseusPosition.y -= 25;
	perseusPosition.x += 25;
	Sword* sword = new Sword(perseusPosition);
	weapons.push_back(sword);
}

void Perseus::useShield() {
	isUsingShield = true;
	if(shieldTimer > 0) {
		shieldTimer -= shieldDecayRate; //decrease shield bar
	}
	else {
		shieldTimer = 0; //clamp timer to zero
		canUseShield = false; //If we have reached zero, we cant use the shield anymore
		isUsingShield = false; //We are no longer using the shield
	}
}

void Perseus::recoverShield() {
	if(shieldTimer < shieldTimerMax) {
		shieldTimer += shieldRecoveryRate; //increase shield bar
	}
	else {
		shieldTimer = shieldTimerMax; //clamp timer to maximum
		canUseShield = true; //The shield has fully recovered
	}
}

vector<Weapons*> Perseus::getWeapons() {
	return weapons;
}

sf::Vector2<float> Perseus::getLocation(){
	return bodySprite.getPosition();
}

bool Perseus::checkCollision(Monster *monster) {
	//Check for Collisions
	sf::Vector2f monsterPosition = monster->getPosition();
	sf::Vector2f size = monster->getSize();
	if (monsterPosition.y + size.y > bodySprite.getPosition().y && monsterPosition.y < bodySprite.getPosition().y + bodySprite.getGlobalBounds().height) {
		if (monsterPosition.x < bodySprite.getPosition().x + bodySprite.getGlobalBounds().width && monsterPosition.x + size.x > bodySprite.getPosition().x) {
			return true;
		}
	}
	return false;
}

void Perseus::hurt() {
	invincibilityTimer = invincibilityFrames;
	isInvincible = true;
	health--;
	if (health == 0) {
		isAlive = false;
	}
}

void Perseus::cleanWeapons(){
	for (unsigned int i=0;i<weapons.size();i++){
		delete weapons[i];
	}
}