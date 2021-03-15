#include "HighScoreInput.h"

HighScoreInput::HighScoreInput(int score)
	:GameState("HighScoreInput"), score(score),
	backgorund("HighscoreInputBackground")
{
	this->font.loadFromFile("C:/Windows/Fonts/Gabriola.ttf");

	this->labelText[0].setString("Game over!");
	this->labelText[1].setString("You managed to get a score of " + std::to_string(score) + "!");
	this->labelText[2].setString("   Please enter your name down below\n(Max ten characters, Min one character)");
	this->labelText[3].setString("Press [Enter] to continue");

	for (int i = 0; i < 4; i++)
	{
		this->labelText[i].setFillColor(sf::Color::Black);
		this->labelText[i].setCharacterSize(30);
		this->labelText[i].setFont(this->font);
		this->labelText[i].setStyle(sf::Text::Bold);
		this->labelText[i].setPosition(WIDTH / 2 - labelText[i].getGlobalBounds().width / 2, 240 + i * 30);
	}

	this->labelText[3].setPosition(labelText[3].getPosition().x, 600);
	this->text.setFillColor(sf::Color::Black);
	this->text.setFont(this->font);
	this->text.setCharacterSize(50);
	this->text.setStyle(sf::Text::Bold);
	this->text.setPosition(WIDTH / 2 - text.getGlobalBounds().width / 2, 450);

	this->done = false;
}

HighScoreInput::~HighScoreInput()
{
	delete[] strArr;
	delete[] intArr;
}

State HighScoreInput::update()
{
	State currState = State::NO_CHANGE;

	if (done)
	{
		writeToFile.open("../Data/Spelprojekt/Highscores.txt", std::ios::app);
		if (writeToFile.is_open())
		{
			writeToFile << this->name << ": " << this->score << std::endl;
			writeToFile.close();

			sortHighscores();
		}

		currState = State::MENU;
	}

	return currState;
}

void HighScoreInput::render()
{
	window.clear();

	window.draw(this->backgorund);

	for (int i = 0; i < 4; i++)
	{
		window.draw(this->labelText[i]);
	}

	window.draw(this->text);

	window.display();
}

void HighScoreInput::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && name.length() >= 1)
			{
				done = true;
			}

			if (event.text.unicode >= 0 && event.text.unicode <= 25 && name.length() <= 10)
			{
				name += (char)(event.text.unicode + 65);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && name != "")
			{
				name.erase(name.length() - 1, 1);
			}

			text.setString(name);
			text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2, text.getPosition().y);
		}
	}
}

void HighScoreInput::sortHighscores()
{
	readFromFile.open("../Data/Spelprojekt/Highscores.txt");
	int nrOfElements = 0;

	this->capacity = 10;
	this->strArr = new std::string[capacity]{};
	this->intArr = new int[capacity]{};

	if (readFromFile.is_open())
	{	
		if (!writeToFile.eof())
		{
			for (std::string line; getline(readFromFile, line);)
			{
				if (line != "")
				{
					strArr[nrOfElements] = line.substr(0, line.find(" ") + 1);
					intArr[nrOfElements] = stoi(line.substr(line.find(" ") + 1, line.length()));

					nrOfElements++;

					if (nrOfElements == capacity)
					{
						capacity *= 2;
						std::string* tempStr = new std::string[capacity]{};
						int* tempInt = new int[capacity] {};

						for (int i = 0; i < nrOfElements - 1; i++)
						{
							tempStr[i] = strArr[i];
							tempInt[i] = intArr[i];
						}

						strArr = tempStr;
						intArr = tempInt;

						tempStr = nullptr;
						tempInt = nullptr;
					}
				}
			}
		}

		readFromFile.close();
	}

	int highestIndex;

	for (int n = 0; n < nrOfElements - 1; n++)
	{
		highestIndex = n;

		for (int i = n + 1; i < nrOfElements; i++)
		{
			if (intArr[i] >= intArr[highestIndex])
			{
				highestIndex = i;
			}
		}

		int intTemp = intArr[n];
		intArr[n] = intArr[highestIndex];
		intArr[highestIndex] = intTemp;

		std::string strTemp = strArr[n];
		strArr[n] = strArr[highestIndex];
		strArr[highestIndex] = strTemp;
	
	}

	writeToFile.open("../Data/Spelprojekt/Highscores.txt", std::ios::trunc);

	if (writeToFile.is_open())
	{	
		for (int i = 0; i < nrOfElements; i++)
		{
			writeToFile << this->strArr[i] << std::to_string(this->intArr[i]) << std::endl;
		}
	}

	writeToFile.close();
}