#include "Game.h"

void Game::handleEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int i = 0; i < PROJECTILE_CAP; i++)
				{
					if (!this->projectiles[i]->isActivated())
					{
						this->player->getProjectile(this->projectiles[i]);
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				if (!this->bomb->isActivated())
				{
					player->getBomb(this->bomb);
				}
			}
		}
	}
}

State Game::update()
{
	State currentState = State::NO_CHANGE;

	elapsedTimeSinceLastUpdate += clock.restart();

	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;

		this->timeSinceLastSpawn = this->enemyTimer.getElapsedTime().asSeconds() - this->lastSpawn;

		this->interface.updateInterface((int)this->enemyTimer.getElapsedTime().asSeconds(), this->player->getHealth());

		this->player->getDirection(window);
		this->player->move();

		if (this->bomb->isActivated())
		{
			this->bomb->move();

			if (this->bomb->isExploding())
			{
				for (int i = 0; i < nrOfEnemies; i++)
				{
					if (this->enemies[i]->isActivated())
					{
						int force = this->bomb->getPushForceTo(*this->enemies[i]);

						if (force > 1)
						{
							this->enemies[i]->bounceBackFrom(*this->bomb, force);
							float dmg = (force / 10) * this->bomb->getDamage();
							this->enemies[i]->looseHealth(dmg);
							if (this->enemies[i]->getHealth() <= 0)
							{
								this->enemiesKilled++;
								this->enemies[i]->respawn();
							}
						}
					}
				}

				this->bomb->respawn();
			}
		}

		for (int i = 0; i < PROJECTILE_CAP; i++)
		{
			if (this->projectiles[i]->isActivated())
			{
				this->projectiles[i]->move();
			}
		}
		
		if (this->timeSinceLastSpawn > enemySpawnTime)
		{
			activateEnemy();
		}

		for (int i = 0; i < nrOfEnemies; i++)
		{
			if (this->enemies[i]->isActivated())
			{
				this->enemies[i]->move();

				if (this->enemies[i]->didHit(*this->player) && !this->enemies[i]->isBacking())
				{
					this->enemies[i]->bounceBackFrom(*this->player, 5);
					this->enemies[i]->looseHealth(this->player->getDamage());

					this->player->bounceBackFrom(*this->enemies[i], 5);
					this->player->looseHealth(this->enemies[i]->getDamage());
				}

				for (int n = 0; n < PROJECTILE_CAP; n++)
				{
					if (this->enemies[i]->didHit(*this->projectiles[n]) && this->projectiles[n]->isActivated())
					{
						this->projectiles[n]->isActivated(false);
						this->enemies[i]->looseHealth(this->projectiles[n]->getDamage());

						if (this->enemies[i]->getHealth() <= 0)
						{
							this->enemiesKilled++;
							this->enemies[i]->respawn();
						}
					}
				}

			}
		}
	}

	if (this->player->getHealth() <= 0)
	{
		currentState = State::HIGHSCORE_INPUT;
	}

	return currentState;
}

void Game::render()
{
	window.clear();

	window.draw(this->backGround);
	window.draw(*this->player);

	if (this->bomb->isActivated())
	{
		window.draw(*this->bomb);
	}
	
	for (int i = 0; i < PROJECTILE_CAP; i++)
	{
		if (projectiles[i]->isActivated())
		{
			window.draw(*this->projectiles[i]);
		}
	}

	for (int i = 0; i < nrOfEnemies; i++)
	{
		if (this->enemies[i]->isActivated())
		{
			window.draw(*this->enemies[i]);
		}
	}

	window.draw(this->interface);

	window.display();
}

Game::Game(int gameMode)
	:timePerFrame(sf::seconds(1.0f / 60.0f)),
	elapsedTimeSinceLastUpdate(sf::Time::Zero),
	lastSpawn(0), timeSinceLastSpawn(0),
	GameState("Game"), backGround("Background"),
	interface(WIDTH)
{	
	setUpGame(gameMode);
	enemyTimer.restart();
}

Game::~Game()
{
	delete this->player;
	delete this->bomb;
	
	for (int i = 0; i < PROJECTILE_CAP; i++)
	{
		delete projectiles[i];
	}

	for (int i = 0; i < nrOfEnemies; i++)
	{
		delete enemies[i];
	}

	delete[] enemies;
}

void Game::run()
{
	while (window.isOpen())
	{
		handleEvents();
		update();
		render();
	}
}

void Game::activateEnemy()
{
	int randEnemy = rand() % nrOfEnemies;

	if (!enemies[randEnemy]->isActivated())
	{
		this->enemies[randEnemy]->isActivated(true);
		this->lastSpawn = enemyTimer.getElapsedTime().asSeconds();
	}

	else
	{
		activateEnemy();
	}
}

void Game::setUpGame(int gameMode)
{

	int nrOfUniqueEnemies = 3;
	
	float bombCooldown;
	float projectileCooldown;

	int walkingSpeed = 1;
	int walkingDamage = 40;
	int walkingHealth = 150;

	int jumpingSpeed = 1;
	int jumpingDamage = 50;
	int jumpingHealth = 100;

	int flyingSpeed = 1;
	int flyingDamage = 50;
	int flyingHealth = 100;

	this->nrOfEnemies = 40;
	this->enemiesKilled = 0;

	if (gameMode == 0)
	{
		this->nrOfEnemies = 20;
		bombCooldown = 1;
		projectileCooldown = 0.3;
		enemySpawnTime = 1;

		walkingSpeed = 1;
		walkingDamage = 20;
		walkingHealth = 100;

		jumpingSpeed = 1;
		jumpingDamage = 30;
		jumpingHealth = 50;

		nrOfUniqueEnemies = 2;
	}

	if (gameMode == 1)
	{
		bombCooldown = 1;
		projectileCooldown = 0.3;
		enemySpawnTime = 1;
	}

	if (gameMode == 2 || gameMode == 3)
	{
		bombCooldown = 3;
		projectileCooldown = 0.4;
		enemySpawnTime = 0.5;
	}

	this->bomb = new Bomb(5, 50, WIDTH, HEIGHT, "Bomb", 0, 100, 100, 5, 0.25f, 1.1f);

	for (int i = 0; i < PROJECTILE_CAP; i++)
	{
		this->projectiles[i] = new Projectile(15, 40, WIDTH, HEIGHT, "Projectile", 0, 225, 100, 6, 0.1f);
	}

	this->enemies = new DynamicEntity*[nrOfEnemies]{ nullptr };

	for (int i = 0; i < nrOfEnemies; i++)
	{
		int startSide = -1;
		if (i % 2 == 0)
		{
			startSide = 1;
		}

		if (i >= 0 && i < 10)
		{
			this->enemies[i] = new WalkingEnemy(walkingSpeed, walkingDamage, WIDTH, HEIGHT, "WalkingEnemy", walkingHealth, 125, 88, 3, 0.75f, 2.0f, startSide);
		}

		if (i >= 10 && i < (nrOfEnemies / 2) + 10)
		{
			this->enemies[i] = new JumpingEnemy(jumpingSpeed, jumpingDamage, WIDTH, HEIGHT, "JumpingEnemy", jumpingHealth, 135.2f, 132.0f, 5, 0.1f, 1.5f, startSide);
		}

		if (i >= (nrOfEnemies / 2 + 10))
		{
			this->enemies[i] = new FlyingEnemy(flyingSpeed, flyingDamage, WIDTH, HEIGHT, "FlyingEnemy", flyingHealth, 250, 200, 4, 0.2f, 0.9f, startSide, 90);

		}
	}

	if (gameMode == 3)
	{
		this->player = new Player(10, 10, WIDTH, HEIGHT, "Player", 1, 315, 512, 14, 0.025f, projectileCooldown, bombCooldown, 0.4f);
	}

	else
	{
		this->player = new Player(10, 10, WIDTH, HEIGHT, "Player", 100, 315, 512, 14, 0.025f, projectileCooldown, bombCooldown, 0.4f);
	}
}

int Game::getScore() const
{
	float time = enemyTimer.getElapsedTime().asSeconds();
	int score = (int)(time * enemiesKilled);
	return score;
}