#include "Background.h"

Background::Background(std::string filename)
{
	this->texture.loadFromFile("../Images/Spelprojekt/" + filename + ".jpg");
	this->sprite.setTexture(texture);
	this->sprite.scale(1, 1);
}

Background::~Background()
{
}

void Background::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
