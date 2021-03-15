#pragma once

#include "Enemy.h"

class FlyingEnemy :public DynamicEntity
{
private:
	int startSide;
	float yPos;
public:
	FlyingEnemy(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling, int startSide, float yPos);
	virtual~FlyingEnemy();

	// Inherited via DynamicEntity
	virtual void move() override;
	virtual void respawn() override;
};