#pragma once

#include "GameState.h"
#include "Background.h"
#include <SFML/Graphics.hpp>

class Menu :public GameState
{
private:
	static const int NONE = -1, START = 0, EXIT = 1, HIGHSCORE = 2, GAMEMODE = 3, GAMEMODE_TXT = 4, GAMEMODE_DESC = 5;
	static const int NROF_GAMEMODES = 4;
	static const int EASY = 0, NORMAL = 1, HARD = 2, HARDCORE = 3;

	int currentGameMode;
	int choice;
	bool done;
	float middle;

	sf::CircleShape triOne;
	sf::CircleShape triTwo;

	sf::Font font;

	sf::Text text[6];

	sf::String gameModes[NROF_GAMEMODES], gameModeDescs[NROF_GAMEMODES];
	sf::String easy, easyDesc, normal, normalDesc, hard, hardDesc, hardCore, hardCoreDesc;

	Background background;
public:
	Menu();
	virtual~Menu();

	void checkIfHovering();
	void setTextAttributes(sf::Text & text, int fontSize, float xPos, float yPos);

	int getGameMode();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;
};