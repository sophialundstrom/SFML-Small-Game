#pragma once

#include "DynamicEntity.h"

class Bomb :public DynamicEntity
{
private:
	bool charging;
	bool exploding;
	bool jumping;
	int nrOfBounces;
	int hDir;
	float vDir, vSpeed;
	float timeSinceJump;
	float lastJump;
	sf::Clock timer;
public:
	Bomb(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling = 1);

	int getPushForceTo(DynamicEntity & entity);
	bool isExploding();

	void cast(int hDir, float playerX, float playerY);

	// Inherited via DynamicEntity
	virtual void move() override;
	virtual void respawn() override;
};
