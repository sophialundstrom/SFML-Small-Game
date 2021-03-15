#pragma once

#include "DynamicEntity.h"

class Projectile :public DynamicEntity
{
private:
	int direction;
public:
	Projectile(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling = 1);

	void cast(int hDir, float playerX, float playerY);
	void setByPlayer(float x, float y);
	
	// Inherited via DynamicEntity
	virtual void move() override;
	virtual void respawn() override;
};