#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling, int startSide, float yPos)
	:DynamicEntity(speed, damage, windowWidth, windowHeight, filename, health, spriteSizeX, spriteSizeY, nrOfSprites, updateTime, scaling), startSide(startSide), yPos(yPos)
{
	respawn();
}

FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::move()
{
	if (isActivated())
	{
		moveSprite(getSpeed() * this->startSide, 0);
	}
}

void FlyingEnemy::respawn()
{
	if (this->startSide == 1)
	{
		setPosition(0 - getBounds().width, yPos);
	}

	else
	{
		setPosition(getWindowWidth(), yPos);
	}

	resetHealth();
	isActivated(false);
}
