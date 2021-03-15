#include "Projectile.h"

Projectile::Projectile(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling)
	:DynamicEntity(speed, damage, windowWidth, windowHeight, filename, health, spriteSizeX, spriteSizeY, nrOfSprites, updateTime, scaling)
{
	this->direction = 0;
	isActivated(false);
}

void Projectile::cast(int hDir, float playerX, float playerY)
{
	this->direction = hDir;
	setByPlayer(playerX, playerY);
	isActivated(true);
}

void Projectile::setByPlayer(float x, float y)
{
	setPosition(x - this->getBounds().width / 2, y - this->getBounds().width / 2);
}

void Projectile::move()
{
	if (isActivated())
	{
		moveSprite(direction * getSpeed(), 0);

		if (this->getBounds().left < 0 || this->getBounds().left + this->getBounds().width > getWindowWidth())
		{
			isActivated(false);
			respawn();
		}
	}
}

void Projectile::respawn()
{
	setPosition(-100, -100);
}
