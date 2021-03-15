#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Background.h"
#include <fstream>

class HighScoreInput :public GameState
{
private:
	Background backgorund;
	std::ifstream readFromFile;
	std::ofstream writeToFile;
	sf::Text labelText[4];
	sf::Text text;
	sf::Font font;
	std::string name;
	int score;
	bool done;

	int capacity;
	std::string* strArr;
	int* intArr;

	void sortHighscores();
public:
	HighScoreInput(int score);
	virtual~HighScoreInput();

	// Inherited via GameState
	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;
};