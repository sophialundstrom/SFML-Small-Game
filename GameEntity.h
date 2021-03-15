#pragma once

#include <SFML/Graphics.hpp>

class GameEntity :public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock clock;
	std::string fileName;
	sf::IntRect rectSourceSprite;

	int nrOfSprites;
	float spriteSizeX, spriteSizeY;
	float updateTime;
	int setRect;
	int scaling;

	float health;
	float maxHealth;

	void switchRectLeft(int integer);
public:
	GameEntity(std::string fileName, float health, float spriteSizeX, float spriteSizeY, int nrOfSprites, float updateTime, float scaling);
	virtual~GameEntity();

	void moveSprite(float horizontal, float vertical);

	sf::FloatRect getBounds() const;

	void setPosition(float x, float y);

	void looseHealth(float amount);
	float getHealth() const;
	void resetHealth();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};