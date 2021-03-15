#pragma once
#include "DynamicEntity.h"
#include "Projectile.h"
#include "Bomb.h"

class Player :public DynamicEntity
{
private:
	static const int LEFT = -1, RIGHT = 1, NONE = 0;

	bool isJumping;
	int castDir;
	int lastCastDir;
	int lastHDir;
	float vDir, vSpeed;
	float groundHeight;

	Projectile* projectile;
	float timeSinceLastCast;
	float lastCast;
	float projectileCooldown;

	Bomb* bomb;
	float timeSinceLastBomb;
	float lastBomb;
	float bombCooldown;

	sf::Clock clock;
public:
	Player(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float projectileCooldown, float bombCooldown, float scaling = 1);
	virtual~Player();

	void getBomb(Bomb* bomb);
	void getProjectile(Projectile* projectile);
	void getDirection(sf::RenderWindow & window);

	// Inherited via DynamicEntity
	virtual void respawn() override;
	virtual void move() override;
};