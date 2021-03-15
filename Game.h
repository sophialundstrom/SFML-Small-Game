#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Background.h"
#include "Projectile.h"
#include "Bomb.h"
#include "WalkingEnemy.h"
#include "JumpingEnemy.h"
#include "FlyingEnemy.h"
#include "GameState.h"
#include "Interface.h"

class Game :public GameState
{
private:
	static const int PROJECTILE_CAP = 3;

	int enemiesKilled;
	float timeSinceLastSpawn;
	float lastSpawn;
	int nrOfEnemies;

	DynamicEntity* *enemies;
	float enemySpawnTime;

	Projectile* projectiles[PROJECTILE_CAP]{ nullptr };
	Bomb* bomb;
	Background backGround;
	Interface interface;
	Player* player;

	sf::Clock enemyTimer;

	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate;
	sf::Time timePerFrame;

	void activateEnemy();
	void setUpGame(int gameMode);

	void handleEvents();
	State update();
	void render();
public:
	int getScore() const;

	Game(int gameMode);
	~Game();
	void run();
};