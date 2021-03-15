#pragma once

#include <SFML/Graphics.hpp>

class Interface :public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Font font;
	sf::Text timeText;
	sf::Text lifeText;
	float windowWidth;
public:
	Interface(float windowWidth);
	void updateInterface(int secondsElapsed, int lifeLeft);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};