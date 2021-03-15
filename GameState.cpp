#include "GameState.h"

GameState::GameState(std::string title)
	:window(sf::VideoMode(WIDTH, HEIGHT), title)
{
}

GameState::~GameState()
{
}
