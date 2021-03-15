#include "JumpingEnemy.h"

JumpingEnemy::JumpingEnemy(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling, int startSide)
	:DynamicEntity(speed, damage, windowWidth, windowHeight, filename, health, spriteSizeX, spriteSizeY, nrOfSprites, updateTime, scaling), startSide(startSide)
{
	respawn();
}

JumpingEnemy::~JumpingEnemy()
{
}

void JumpingEnemy::move()
{
	timeSinceLanded = clock.getElapsedTime().asSeconds() - timeLanded;

	if (this->getBounds().top == yPos && timeSinceLanded > 1.5)
	{
		isJumping = true;
	}

	if (isJumping || isBacking())
	{
		this->vDir = -(pow(this->vSpeed, 2)) + 1;
		this->vSpeed += 0.02f;
		
		moveSprite(getSpeed() * startSide * getPushForce(), vDir * getPushForce() * getSpeed());

		if (this->getBounds().top > yPos)
		{
			this->setPosition(this->getBounds().left, yPos);
			this-> vDir = 0;
			this->vSpeed = -sqrt(2);
			setPushForce(3);
			isBacking(false);
			this->isJumping = false; 
			this->timeLanded = clock.getElapsedTime().asSeconds();
		}
	}

	else
	{
		moveSprite(0, 0);
	}
}

void JumpingEnemy::respawn()
{
	this->yPos = rand() % 150 + 400;
	this->vDir = 0;
	this->vSpeed = -sqrt(2);
	this->timeLanded = 0;
	setPushForce(3);

	if (startSide == 1)
	{
		this->setPosition(0 - this->getBounds().width, yPos);
	}

	else
	{
		this->setPosition(getWindowWidth(), yPos);
	}

	resetHealth();
	isActivated(false);
}
