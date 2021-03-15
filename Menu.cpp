#include "Menu.h"

Menu::Menu()
	:GameState("Menu"),
	background("MenuBackground")
{
	this->done = false;
	choice = NONE;

	this->triOne = sf::CircleShape(15, 3);
	this->triTwo = sf::CircleShape(15, 3);

	this->triOne.rotate(270);
	this->triTwo.rotate(90);

	this->easy = "EASY";
	this->easyDesc = "Less and slower enemies.";

	this->normal = "NORMAL";
	this->normalDesc = "A normal game experience.";

	this->hard = "HARD";
	this->hardDesc = "More and faster enemies.";

	this->hardCore = "HARDCORE";
	this->hardCoreDesc = "One life, one chance.";

	int nrOfGamemodes = 0;

	this->gameModes[nrOfGamemodes] = easy;
	this->gameModeDescs[nrOfGamemodes++] = easyDesc;

	this->gameModes[nrOfGamemodes] = normal;
	this->gameModeDescs[nrOfGamemodes++] = normalDesc;

	this->gameModes[nrOfGamemodes] = hard;
	this->gameModeDescs[nrOfGamemodes++] = hardDesc;

	this->gameModes[nrOfGamemodes] = hardCore;
	this->gameModeDescs[nrOfGamemodes++] = hardCoreDesc;

	this->font.loadFromFile("C:/Windows/Fonts/Gabriola.ttf");

	text[START].setString("START");
	text[EXIT].setString("EXIT");
	text[HIGHSCORE].setString("HIGHSCORES");
	text[GAMEMODE].setString("GAMEMODE");
	text[GAMEMODE_TXT].setString(normal);
	text[GAMEMODE_DESC].setString(normalDesc);


	middle = 240;

	setTextAttributes(text[START], 50, middle, 135);
	setTextAttributes(text[GAMEMODE], 50, middle, 290);
	setTextAttributes(text[GAMEMODE_TXT], 40, middle, 365);
	setTextAttributes(text[GAMEMODE_DESC], 35, middle, 420);
	setTextAttributes(text[HIGHSCORE], 50, middle, 555);
	setTextAttributes(text[EXIT], 50, middle, 715);
	

	this->triOne.setPosition(this->text[GAMEMODE_TXT].getGlobalBounds().left - 80, text[GAMEMODE_TXT].getPosition().y + 40);
	this->triTwo.setPosition(this->text[GAMEMODE_TXT].getGlobalBounds().left + this->text[GAMEMODE_TXT].getGlobalBounds().width + 80, text[GAMEMODE_TXT].getPosition().y + 10);

	this->currentGameMode = NORMAL;
}

Menu::~Menu()
{
}

void Menu::checkIfHovering()
{
	if (sf::Mouse::getPosition(window).x >= this->text[EXIT].getGlobalBounds().left &&
		sf::Mouse::getPosition(window).x <= this->text[EXIT].getGlobalBounds().left + this->text[EXIT].getGlobalBounds().width &&
		sf::Mouse::getPosition(window).y >= this->text[EXIT].getGlobalBounds().top &&
		sf::Mouse::getPosition(window).y <= this->text[EXIT].getGlobalBounds().top + this->text[EXIT].getGlobalBounds().height)
	{
		this->text[EXIT].setFillColor(sf::Color(100, 100, 100));
	}

	else if (sf::Mouse::getPosition(window).x >= this->text[START].getGlobalBounds().left &&
		sf::Mouse::getPosition(window).x <= this->text[START].getGlobalBounds().left + this->text[START].getGlobalBounds().width &&
		sf::Mouse::getPosition(window).y >= this->text[START].getGlobalBounds().top &&
		sf::Mouse::getPosition(window).y <= this->text[START].getGlobalBounds().top + this->text[START].getGlobalBounds().height)
	{
		this->text[START].setFillColor(sf::Color(100, 100, 100));
	}

	else if (sf::Mouse::getPosition(window).x >= this->text[HIGHSCORE].getGlobalBounds().left &&
		sf::Mouse::getPosition(window).x <= this->text[HIGHSCORE].getGlobalBounds().left + this->text[HIGHSCORE].getGlobalBounds().width &&
		sf::Mouse::getPosition(window).y >= this->text[HIGHSCORE].getGlobalBounds().top &&
		sf::Mouse::getPosition(window).y <= this->text[HIGHSCORE].getGlobalBounds().top + this->text[HIGHSCORE].getGlobalBounds().height)
	{
		this->text[HIGHSCORE].setFillColor(sf::Color(100, 100, 100));
	}

	else if (this->triOne.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		this->triOne.setFillColor(sf::Color(100, 100, 100));
	}

	else if (this->triTwo.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		this->triTwo.setFillColor(sf::Color(100, 100, 100));
	}

	else
	{
		this->text[EXIT].setFillColor(sf::Color::Black);
		this->text[START].setFillColor(sf::Color::Black);
		this->text[HIGHSCORE].setFillColor(sf::Color::Black);
		this->triOne.setFillColor(sf::Color::Black);
		this->triTwo.setFillColor(sf::Color::Black);
	}
}

void Menu::setTextAttributes(sf::Text & text, int fontSize, float xPos, float yPos)
{
	text.setFont(this->font);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color::Black);
	text.setPosition((xPos - (text.getGlobalBounds().width / 2)), yPos);
}

int Menu::getGameMode()
{
	return this->currentGameMode;
}

void Menu::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (sf::Mouse::getPosition(window).x >= this->text[EXIT].getGlobalBounds().left &&
					sf::Mouse::getPosition(window).x <= this->text[EXIT].getGlobalBounds().left + this->text[EXIT].getGlobalBounds().width &&
					sf::Mouse::getPosition(window).y >= this->text[EXIT].getGlobalBounds().top &&
					sf::Mouse::getPosition(window).y <= this->text[EXIT].getGlobalBounds().top + this->text[EXIT].getGlobalBounds().height)
				{
					choice = EXIT;
					done = true;
				}

				if (sf::Mouse::getPosition(window).x >= this->text[START].getGlobalBounds().left &&
					sf::Mouse::getPosition(window).x <= this->text[START].getGlobalBounds().left + this->text[START].getGlobalBounds().width &&
					sf::Mouse::getPosition(window).y >= this->text[START].getGlobalBounds().top &&
					sf::Mouse::getPosition(window).y <= this->text[START].getGlobalBounds().top + this->text[START].getGlobalBounds().height)
				{
					choice = START;
					done = true;
				}

				if (sf::Mouse::getPosition(window).x >= this->text[HIGHSCORE].getGlobalBounds().left &&
					sf::Mouse::getPosition(window).x <= this->text[HIGHSCORE].getGlobalBounds().left + this->text[HIGHSCORE].getGlobalBounds().width &&
					sf::Mouse::getPosition(window).y >= this->text[HIGHSCORE].getGlobalBounds().top &&
					sf::Mouse::getPosition(window).y <= this->text[HIGHSCORE].getGlobalBounds().top + this->text[HIGHSCORE].getGlobalBounds().height)
				{
					choice = HIGHSCORE;
					done = true;
				}

				if (this->triOne.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					if (this->currentGameMode == EASY)
					{
						currentGameMode = 4;
					}

					this->currentGameMode--;

					this->text[GAMEMODE_TXT].setString(gameModes[currentGameMode]);
					this->text[GAMEMODE_TXT].setPosition(middle - text[GAMEMODE_TXT].getGlobalBounds().width / 2, text[GAMEMODE_TXT].getPosition().y);

					this->text[GAMEMODE_DESC].setString(gameModeDescs[currentGameMode]);
					this->text[GAMEMODE_DESC].setPosition(middle - text[GAMEMODE_DESC].getGlobalBounds().width / 2, text[GAMEMODE_DESC].getPosition().y);
				}

				if (this->triTwo.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					if (this->currentGameMode == HARDCORE)
					{
						currentGameMode = -1;
					}

					this->currentGameMode++;

					this->text[GAMEMODE_TXT].setString(gameModes[currentGameMode]);
					this->text[GAMEMODE_TXT].setPosition(middle - text[GAMEMODE_TXT].getGlobalBounds().width / 2, text[GAMEMODE_TXT].getPosition().y);

					this->text[GAMEMODE_DESC].setString(gameModeDescs[currentGameMode]);
					this->text[GAMEMODE_DESC].setPosition(middle - text[GAMEMODE_DESC].getGlobalBounds().width / 2, text[GAMEMODE_DESC].getPosition().y);
				}
			}
		}
	}
}

void Menu::render()
{
	window.clear();

	window.draw(background);

	for (int i = 0; i < 6; i++)
	{
		window.draw(text[i]);
	}

	window.draw(triOne);
	window.draw(triTwo);

	window.display();
}

State Menu::update()
{
	State currentState = State::NO_CHANGE;

	checkIfHovering();

	if (choice == EXIT && this->done)
	{
		currentState = State::EXIT;
	}

	if (choice == START && this->done)
	{
		currentState = State::PLAY;
	}

	if (choice == HIGHSCORE && this->done)
	{
		currentState = State::HIGHSCORE;
	}

	return currentState;
}