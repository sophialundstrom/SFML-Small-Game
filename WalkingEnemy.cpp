#include "WalkingEnemy.h"

WalkingEnemy::WalkingEnemy(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling, int startSide)
	:DynamicEntity(speed, damage, windowWidth, windowHeight, filename, health, spriteSizeX, spriteSizeY, nrOfSprites, updateTime, scaling), startSide(startSide)
{
	respawn();
}

void WalkingEnemy::move()
{
	if (!isBacking())
	{
		this->moveSprite(getSpeed() * this->startSide, 0);
	}
	
	if (isBacking())
	{
		this->vDir = -(pow(this->vSpeed, 2)) + 1;
		this->vSpeed += 0.02f;
		moveSprite(getSpeed() * getPushForce() * getHorizontalDir(), this->vDir * getPushForce());

		if (this->getBounds().top > yPos)
		{
			this->setPosition(this->getBounds().left, yPos);
			vDir = 0;
			vSpeed = -sqrt(2);
			isBacking(false);
		}
	}
}

void WalkingEnemy::respawn()
{
	this->yPos = rand() % 150 + 400;
	this->vDir = 0;
	this->vSpeed = -sqrt(2);

	if (startSide == 1)
	{
		this->setPosition(0 - this->getBounds().width, yPos);
	}

	else
	{
		this->setPosition(getWindowWidth() + this->getBounds().width, yPos);
	}

	resetHealth();
	isActivated(false);
	isBacking(false);
}
