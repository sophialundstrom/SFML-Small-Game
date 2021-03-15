#include "HighScore.h"

void HighScore::checkIfHovering()
{
	if (sf::Mouse::getPosition(window).x >= this->returnText.getGlobalBounds().left &&
		sf::Mouse::getPosition(window).x <= this->returnText.getGlobalBounds().left + this->returnText.getGlobalBounds().width &&
		sf::Mouse::getPosition(window).y >= this->returnText.getGlobalBounds().top &&
		sf::Mouse::getPosition(window).y <= this->returnText.getGlobalBounds().top + this->returnText.getGlobalBounds().height)
	{
		this->returnText.setFillColor(sf::Color(100, 100, 100));
	}

	else
	{
		this->returnText.setFillColor(sf::Color::Black);
	}
}

HighScore::HighScore()
	:GameState("Highscores"),
	background("HighscoreBackground")
{
	stream.open("../Data/Spelprojekt/Highscores.txt");
	nrOfPlayers = 0;

	if (stream.is_open())
	{
		std::string name;
		int score;
		
		for (int i = 0; i < 5; i++)
		{
			if (!stream.eof())
			{
				std::string line;
				std::getline(stream, line);

				if (line != "")
				{
					nameData[nrOfPlayers] = line.substr(0, line.find(" ") + 1);
					scoreData[nrOfPlayers] = stoi(line.substr(line.find(" ") + 1, line.length()));
					nrOfPlayers++;
				}
			}
		}
		
		stream.close();
	}

	this->font.loadFromFile("C:/Windows/Fonts/Gabriola.ttf");

	this->topFive.setString("Highscores");
	this->topFive.setFont(this->font);
	this->topFive.setCharacterSize(50);
	this->topFive.setPosition(WIDTH / 2 - this->topFive.getGlobalBounds().width / 2, 110);
	this->topFive.setFillColor(sf::Color::Black);

	this->returnText.setString("Return to Main menu");
	this->returnText.setFont(this->font);
	this->returnText.setCharacterSize(40);
	this->returnText.setPosition(WIDTH / 2 - this->returnText.getGlobalBounds().width / 2, 720);
	this->returnText.setFillColor(sf::Color::Black);

	int sets = 0;
	for (int i = 0; i < nrOfPlayers * 2; i++)
	{
		this->players[i].setFont(this->font);
		this->players[i].setFillColor(sf::Color::Black);
		this->players[i].setCharacterSize(40);
		this->players[i].setString(nameData[sets]);
		this->players[i].setPosition(WIDTH / 2 - this->players[i].getGlobalBounds().width / 2, 180 + (55 * i));

		this->players[i + 1].setFont(this->font);
		this->players[i + 1].setFillColor(sf::Color::Black);
		this->players[i + 1].setCharacterSize(40);
		this->players[i + 1].setString(std::to_string(scoreData[sets]));
		this->players[i + 1].setPosition(WIDTH / 2 - this->players[i + 1].getGlobalBounds().width / 2, players[i].getPosition().y + 30);
		i++;
		sets++;
	}
}

HighScore::~HighScore()
{
}

State HighScore::update()
{
	State currentState = State::NO_CHANGE;

	checkIfHovering();

	if (done)
	{
		currentState = State::MENU;
	}

	return currentState;
}

void HighScore::render()
{
	window.clear();

	window.draw(this->background);
	window.draw(this->topFive);
	window.draw(this->returnText);
	
	for (int i = 0; i < nrOfPlayers * 2; i++)
	{
		window.draw(players[i]);
	}

	window.display();
}

void HighScore::handleEvents()
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
				if (sf::Mouse::getPosition(window).x >= this->returnText.getGlobalBounds().left &&
					sf::Mouse::getPosition(window).x <= this->returnText.getGlobalBounds().left + this->returnText.getGlobalBounds().width &&
					sf::Mouse::getPosition(window).y >= this->returnText.getGlobalBounds().top &&
					sf::Mouse::getPosition(window).y <= this->returnText.getGlobalBounds().top + this->returnText.getGlobalBounds().height)
				{
					done = true;
				}
			}
		}
	}
}
