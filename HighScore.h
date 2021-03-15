#pragma once
#include "GameState.h"
#include "Background.h"
#include <SFML/Graphics.hpp>
#include <fstream>

class HighScore :public GameState
{
private:
	Background background;

	std::ifstream stream;

	std::string nameData[5];
	int scoreData[5];

	sf::Font font;
	sf::Text returnText;
	sf::Text topFive;
	sf::Text players[10];

	int nrOfPlayers;
	bool done;

	void checkIfHovering();
public:
	HighScore();
	virtual~HighScore();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;
};