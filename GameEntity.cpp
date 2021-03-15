#include "GameEntity.h"

void GameEntity::switchRectLeft(int integer)
{
	if (setRect != integer)
	{
		setRect = integer;

		if (integer == 0 || integer == 2 || integer == 4)
		{
			rectSourceSprite.left = 0;
		}

		if (integer == 1 || integer == 3)
		{
			rectSourceSprite.left = nrOfSprites * spriteSizeX;
		}
	}
}

GameEntity::GameEntity(std::string fileName, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling)
	:health(health), spriteSizeX(spriteSizeX), spriteSizeY(spriteSizeY), nrOfSprites(nrOfSprites), updateTime(updateTime), fileName(fileName), maxHealth(health)
{
	this->rectSourceSprite = sf::IntRect(0, 0, spriteSizeX, spriteSizeY);
	this->texture.loadFromFile("../Images/SpelProjekt/" + fileName + "Spritesheet.png");
	this->sprite = sf::Sprite(texture, rectSourceSprite);
	this->sprite.scale(scaling, scaling);
	this->setRect = -1;
}

GameEntity::~GameEntity()
{
}

void GameEntity::moveSprite(float horizontal, float vertical)
{
	if (horizontal == 0)
	{
		switchRectLeft(4);
		rectSourceSprite.top = spriteSizeY * 6;

		if (clock.getElapsedTime().asSeconds() > updateTime * 3)
		{
			if (rectSourceSprite.left >= (nrOfSprites - 1) * spriteSizeX)
			{
				rectSourceSprite.left = 0;
			}

			else
			{
				rectSourceSprite.left += spriteSizeX;
			}

			sprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}
	}

	if (horizontal > 0 && (vertical > 0 || vertical < 0))
	{	
		if (vertical > 0)
		{
			switchRectLeft(1);
			rectSourceSprite.top = spriteSizeY * 3;

			if (clock.getElapsedTime().asSeconds() > updateTime * 0.75)
			{
				if (rectSourceSprite.left <= 0)
				{
					rectSourceSprite.left = 0;
				}

				else
				{
					rectSourceSprite.left -= spriteSizeX;
				}

				sprite.setTextureRect(rectSourceSprite);
				clock.restart();
			}
		}

		if (vertical < 0)
		{
			switchRectLeft(3);
			rectSourceSprite.top = spriteSizeY * 2;

			if (clock.getElapsedTime().asSeconds() > updateTime * 0.75)
			{
				if (rectSourceSprite.left <= 0)
				{
					rectSourceSprite.left = 0;
				}

				else
				{
					rectSourceSprite.left -= spriteSizeX;
				}
		
				sprite.setTextureRect(rectSourceSprite);
				clock.restart();
			}
		}
	}

	if (horizontal < 0 && (vertical > 0 || vertical < 0))
	{
		if (vertical > 0)
		{
			switchRectLeft(0);
			rectSourceSprite.top = spriteSizeY * 5;

			if (clock.getElapsedTime().asSeconds() > updateTime)
			{
				if (rectSourceSprite.left >= (nrOfSprites - 1) * spriteSizeX)
				{
					rectSourceSprite.left = (nrOfSprites - 1) * spriteSizeX;
				}

				else
				{
					rectSourceSprite.left += spriteSizeX;
				}

				sprite.setTextureRect(rectSourceSprite);
				clock.restart();
			}
		}

		if (vertical < 0)
		{
			switchRectLeft(2);
			rectSourceSprite.top = spriteSizeY * 4;

			if (clock.getElapsedTime().asSeconds() > updateTime)
			{
				if (rectSourceSprite.left >= (nrOfSprites - 1) * spriteSizeX)
				{
					rectSourceSprite.left = (nrOfSprites - 1) * spriteSizeX;
				}

				else
				{
					rectSourceSprite.left += spriteSizeX;
				}

				sprite.setTextureRect(rectSourceSprite);
				clock.restart();
			}
		}
	}

	if (horizontal > 0 && vertical == 0)
	{
		switchRectLeft(0);
		rectSourceSprite.top = spriteSizeY;

		if (clock.getElapsedTime().asSeconds() > updateTime)
		{
			if (rectSourceSprite.left <= 0)
			{
				rectSourceSprite.left = (nrOfSprites - 1) * spriteSizeX;
			}

			else
			{
				rectSourceSprite.left -= spriteSizeX;
			}

			sprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}
	}

	if (horizontal < 0 && vertical == 0)
	{
		switchRectLeft(0);
		rectSourceSprite.top = 0;
		if (clock.getElapsedTime().asSeconds() > updateTime)
		{
			if (rectSourceSprite.left >= (nrOfSprites - 1) * spriteSizeX)
			{
				rectSourceSprite.left = 0;
			}
			else
			{
				rectSourceSprite.left += spriteSizeX;
			}

			sprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}
	}

	this->sprite.move(horizontal, vertical);
}

sf::FloatRect GameEntity::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void GameEntity::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void GameEntity::looseHealth(float amount)
{
	this->health -= amount;
}

float GameEntity::getHealth() const
{
	return this->health;
}

void GameEntity::resetHealth()
{
	this->health = this->maxHealth;
}

void GameEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
