#pragma once
#include "DynamicEntity.h"

class JumpingEnemy :public DynamicEntity
{
private:
	bool isJumping;
	int startSide;
	float yPos;
	float vDir, vSpeed;
	float timeSinceLanded;
	float timeLanded;
	sf::Clock clock;
public:
	JumpingEnemy(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling, int startSide);
	virtual~JumpingEnemy();

	// Inherited via DynamicEntity
	virtual void move() override;
	virtual void respawn() override;
};