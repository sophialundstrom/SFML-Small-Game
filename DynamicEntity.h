#pragma once
#include "GameEntity.h"

class DynamicEntity :public GameEntity
{
private:
	float speed;
	float damage;

	bool backing;
	bool activated;
	int hDir;
	float pushForce;

	float windowWidth, windowHeight;
	static const int LEFT = -1, RIGHT = 1, NONE = 0;
public:
	DynamicEntity(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling);
	virtual~DynamicEntity();

	float getSpeed() const;
	float getDamage() const;

	bool isBacking() const;
	void isBacking(bool boolean);

	bool isActivated() const;
	void isActivated(bool boolean);

	float getWindowWidth() const;
	float getWindowHeight() const;

	int getHorizontalDir() const;
	void setHorizontalDir(float direction);

	float getPushForce() const;
	void setPushForce(float forceAmount);

	virtual void move() = 0;
	virtual void respawn() = 0;

	void bounceBackFrom(GameEntity & entity, float strength);
	bool didHit(GameEntity & entity);
};