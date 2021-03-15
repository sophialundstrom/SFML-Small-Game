#include "Bomb.h"

Bomb::Bomb(float speed, float damage, float windowWidth, float windowHeight, std::string filename, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling)
	:DynamicEntity(speed, damage, windowWidth, windowHeight, filename, health, spriteSizeX, spriteSizeY, nrOfSprites, updateTime, scaling)
{
	respawn();
}

int Bomb::getPushForceTo(DynamicEntity & entity)
{
	float distance = sqrt(pow(((entity.getBounds().left + entity.getBounds().width) - (this->getBounds().left + this->getBounds().width)), 2));
	float force = 1;

	if (distance < 400 && (this->getBounds().top - entity.getBounds().top < 400))
	{
		force += 4;

		if (distance < 200)
		{
			force += 5;

			if (distance < 100)
			{
				force += 5;

				if (distance < 50)
				{
					force += 5;
				}
			}
		}
	}

	return force;
}

bool Bomb::isExploding()
{
	return this->exploding;
}

void Bomb::cast(int hDir, float playerX, float playerY)
{
	isActivated(true);
	this->hDir = hDir;
	setPosition(playerX, playerY - getBounds().height);
}

void Bomb::move()
{
	if (isActivated() & !exploding)
	{
		if (getBounds().left < 0 || getBounds().left + getBounds().width > getWindowWidth())
		{
			hDir *= -1;
		}

		if (charging)
		{
			if (nrOfBounces < 3)
			{
				timeSinceJump = this->timer.getElapsedTime().asSeconds() - lastJump;

				if ((timeSinceJump > 0.5 && getBounds().top == 500) || (nrOfBounces == 0 && getBounds().top == 500 && timeSinceJump > 0.1))
				{
					jumping = true;
				}

				if (jumping)
				{
					this->vDir = -(pow(vSpeed, 2)) + 1;
					vSpeed += 0.02f;
					moveSprite(0, vDir * 3);

					if (getBounds().top >= 500)
					{
						setPosition(getBounds().left, 500);
						lastJump = timer.getElapsedTime().asSeconds();
						vSpeed = -sqrt(2);
						hDir = 0;
						vDir = 0;
						nrOfBounces++;
						jumping = false;
					}
				}
			}

			if (nrOfBounces >= 3)
			{
				exploding = true;
				hDir = 0;
				vDir = 0;
				vSpeed = -sqrt(2);
			}
		}

		if (getBounds().top < 500 && !charging)
		{
			this->vDir = -(pow(vSpeed, 2)) + 1;
			vSpeed += 0.025f;
			moveSprite(this->getSpeed() * hDir * 3, vDir * 8 * getSpeed());

			if (getBounds().top >= 500)
			{
				setPosition(getBounds().left, 500);
				charging = true;
				this->timer.restart();
				vSpeed = -sqrt(2);
				hDir = 0;
				vDir = 0;
			}
		}
	}
}

void Bomb::respawn()
{
	setPosition(-100, -100);
	isActivated(false);
	exploding = false;
	charging = false;
	this->nrOfBounces = 0;
	this->hDir = 0;
	this->vDir = 0;
	this->vSpeed = -sqrt(2);
	this->timeSinceJump = 0;
	this->lastJump = 0;
	this->jumping = false;
}
