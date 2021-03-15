#include "Menu.h"
#include "Game.h"
#include "HighScoreInput.h"
#include "HighScore.h"
#include <ctime>

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#endif


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(unsigned int(time(0)));

	GameState *current = nullptr;
	State currentState = State::NO_CHANGE;

	current = new Menu();
	currentState = State::MENU;

	int score = 0;
	int gameMode = 0;

	while (currentState != State::EXIT)
	{
		current->handleEvents();
		currentState = current->update();

		if (currentState != State::NO_CHANGE)
		{
			switch (currentState)
			{
			case State::MENU:
				delete current;
				current = new Menu();
				break;
			case State::PLAY:
				gameMode = dynamic_cast<Menu*>(current)->getGameMode();
				delete current;
				current = new Game(gameMode);
				break;
			case State::HIGHSCORE_INPUT:
				score = dynamic_cast<Game*>(current)->getScore();
				delete current;
				current = new HighScoreInput(score);
				break;
			case State::HIGHSCORE:
				delete current;
				current = new HighScore();
				break;
			}
		}
		current->render();
	}

	delete current;
	return 0;
}