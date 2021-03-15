#pragma once

#include <SFML/Graphics.hpp>

class Background :public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Background(std::string filename);
	virtual~Background();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};