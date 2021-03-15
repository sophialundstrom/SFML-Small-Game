#include "Player.h"

Player::Player(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float projectileCooldown, float bombCooldown, float scaling)
	:DynamicEntity(speed, damage, windowWidth, windowHeight, filename, health, spriteSizeX, spriteSizeY, nrOfSprites, updateTime, scaling),
	projectileCooldown(projectileCooldown), bombCooldown(bombCooldown)
{
	this->vSpeed = -sqrt(2);
	this->vDir = NONE;
	this->isJumping = false;
	this->groundHeight = windowHeight - 200 - this->getBounds().height;
	this->timeSinceLastCast = 0;
	this->timeSinceLastBomb = timeSinceLastCast;
	this->lastCast = 0;
	this->lastBomb = 0;
	this->lastHDir = LEFT;
	this->castDir = NONE;
	this->lastCastDir = LEFT;
	respawn();
}

Player::~Player()
{
}

void Player::getBomb(Bomb * bomb)
{
	this->bomb = bomb;
}

void Player::getProjectile(Projectile * projectile)
{
	this->projectile = projectile;
}

void Player::getDirection(sf::RenderWindow & window)
{
	if (sf::Mouse::getPosition(window).x < getBounds().left)
	{
		this->castDir = LEFT;
		this->lastCastDir = castDir;
	}

	if (sf::Mouse::getPosition(window).x > getBounds().left + getBounds().width)
	{
		this->castDir = RIGHT;
		this->lastCastDir = castDir;
	}

	if (sf::Mouse::getPosition(window).x >= getWindowWidth() / 2 - getBounds().width / 2 && sf::Mouse::getPosition(window).x <= getWindowWidth() / 2 + getBounds().width / 2)
	{
		this->castDir = NONE;
	}
}

void Player::respawn()
{
	this->setPosition(getWindowWidth() / 2 - this->getBounds().width / 2, groundHeight);
}

void Player::move()
{
	this->timeSinceLastBomb = clock.getElapsedTime().asSeconds() - lastBomb;
	this->timeSinceLastCast = clock.getElapsedTime().asSeconds() - lastCast;

	this->vDir = NONE;
	setHorizontalDir(NONE);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->getBounds().top == groundHeight)
		{
			isJumping = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		setHorizontalDir(LEFT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		setHorizontalDir(RIGHT);
	}

	if (isJumping || isBacking())
	{
		this->vDir = -(pow(vSpeed, 2)) + 1;
		vSpeed += 0.02f;
		if (vDir == 0)
		{
			vDir += 0.001;
		}
	}

	if ((getHorizontalDir() == LEFT && getBounds().left < 0) || (getHorizontalDir() == RIGHT && getBounds().left + getBounds().width > getWindowWidth()))
	{
		setHorizontalDir(NONE);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->projectile != nullptr && this->timeSinceLastCast > projectileCooldown)
	{
		this->projectile->cast(lastCastDir, this->getBounds().left + this->getBounds().width / 2, this->getBounds().top + this->getBounds().height / 2);
		this->projectile = nullptr;
		this->lastCast = clock.getElapsedTime().asSeconds();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->bomb != nullptr && this->timeSinceLastBomb > bombCooldown)
	{
		this->bomb->cast(lastCastDir, this->getBounds().left + this->getBounds().width / 2, this->getBounds().top);
		this->bomb = nullptr;
		this->lastBomb = clock.getElapsedTime().asSeconds();
	}

	this->moveSprite(this->getSpeed() * getHorizontalDir(), this->getSpeed() * this->vDir * 4);

	if (this->getBounds().top > groundHeight)
	{
		this->setPosition(this->getBounds().left, groundHeight);
		vDir = NONE;
		vSpeed = -sqrt(2);
		isJumping = false;
		isBacking(false);
	}
}