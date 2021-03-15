#include "DynamicEntity.h"

DynamicEntity::DynamicEntity(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling)
	:GameEntity(filename, health, spriteSizeX, spriteSizeY, nrOfSprites, updateTime, scaling), damage(damage), speed(speed), windowWidth(windowWidth), windowHeight(windowHeight)
{
	this->hDir = NONE;
	this->backing = false;
	this->pushForce = 1.0f;
}

DynamicEntity::~DynamicEntity()
{
}

float DynamicEntity::getSpeed() const
{
	return this->speed;
}

float DynamicEntity::getDamage() const
{
	return this->damage;
}

bool DynamicEntity::isBacking() const
{
	return this->backing;
}

void DynamicEntity::isBacking(bool boolean)
{
	this->backing = boolean;
}

bool DynamicEntity::isActivated() const
{
	return this->activated;
}

void DynamicEntity::isActivated(bool boolean)
{
	this->activated = boolean;
}

float DynamicEntity::getWindowWidth() const
{
	return this->windowWidth;
}

float DynamicEntity::getWindowHeight() const
{
	return this->windowHeight;
}

int DynamicEntity::getHorizontalDir() const
{
	return this->hDir;
}

void DynamicEntity::setHorizontalDir(float direction)
{
	this->hDir = direction;
}

float DynamicEntity::getPushForce() const
{
	return this->pushForce;
}

void DynamicEntity::setPushForce(float forceAmount)
{
	this->pushForce = forceAmount;
}

void DynamicEntity::bounceBackFrom(GameEntity & entity, float strength)
{
	if ((this->getBounds().left + this->getBounds().width / 2) < (entity.getBounds().left + entity.getBounds().width / 2))
	{
		setHorizontalDir(LEFT);
	}

	if ((this->getBounds().left + this->getBounds().width / 2) > (entity.getBounds().left + entity.getBounds().width / 2))
	{
		setHorizontalDir(RIGHT);
	}

	this->setPushForce(strength);
	isBacking(true);
}

bool DynamicEntity::didHit(GameEntity & entity)
{
	bool boolean = false;

	if (this->getBounds().intersects(entity.getBounds()))
	{
		boolean = true;
	}
	return boolean;
}