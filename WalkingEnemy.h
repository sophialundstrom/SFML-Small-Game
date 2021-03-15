#pragma once

#include "DynamicEntity.h"

class WalkingEnemy :public DynamicEntity
{
private:
	int startSide;
	float vSpeed;
	float vDir;
	float yPos;
public:
	WalkingEnemy(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling, int startSide);

	// Inherited via DynamicEntity
	virtual void move() override;
	virtual void respawn() override;
};