#include "Interface.h"

Interface::Interface(float windowWidth)
	:windowWidth(windowWidth)
{
	this->font.loadFromFile("C:/Windows/Fonts/Gabriola.ttf");
	this->lifeText.setFont(font);
	this->timeText.setFont(font);

	this->lifeText.setStyle(sf::Text::Bold);
	this->lifeText.setFillColor(sf::Color::Black);
	this->lifeText.setString(" ");
	this->lifeText.setPosition(windowWidth / 2 - lifeText.getGlobalBounds().width / 2, 70);
	this->lifeText.setCharacterSize(35);

	this->timeText.setStyle(sf::Text::Bold);
	this->timeText.setFillColor(sf::Color::Black);
	this->timeText.setString(" ");
	this->timeText.setPosition(windowWidth / 2 - timeText.getGlobalBounds().width / 2, 15);
	this->timeText.setCharacterSize(35);

	this->texture.loadFromFile("../Images/Spelprojekt/UI.png");
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.75, 0.75);
	this->sprite.setPosition(windowWidth / 2 - sprite.getGlobalBounds().width / 2, 0);
}

void Interface::updateInterface(int secondsElapsed, int lifeLeft)
{
	this->timeText.setString("TIME ELAPSED: " + std::to_string(secondsElapsed));
	this->lifeText.setString("HP: " + std::to_string(lifeLeft));

	this->timeText.setPosition(this->windowWidth / 2 - timeText.getGlobalBounds().width / 2, timeText.getPosition().y);
	this->lifeText.setPosition(this->windowWidth / 2 - lifeText.getGlobalBounds().width / 2, lifeText.getPosition().y);
}

void Interface::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(this->timeText);
	target.draw(this->lifeText);
}
