#pragma once

#include <SFML\Graphics.hpp>
#include "State.h"
#include <string>

class GameState
{
protected:
	float WIDTH = 1600, HEIGHT = 900;
	sf::RenderWindow window;
public:
	GameState(std::string title);
	virtual ~GameState();
	virtual State update() = 0;
	virtual void render() = 0;
	virtual void handleEvents() = 0;
};
