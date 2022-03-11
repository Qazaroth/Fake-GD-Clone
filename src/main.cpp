#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "utils/Output.h"
#include "utils/Timer.h"
#include "Level/Level.h"

int main()
{
	Level mainLvl("res/data/levels/0.json");

	sf::RenderWindow window(sf::VideoMode(800, 600), "Fake GD Clone", sf::Style::Default);
	sf::Vector2u windowSize = window.getSize();

	unsigned int windWidth = windowSize.x;
	unsigned int windHeight = windowSize.y;

	sf::Sprite bg;
	sf::Texture bgTexture;

	if (!bgTexture.loadFromFile(mainLvl.getLevelBG()))
	{
		Output::error("Error occured while loading background file!");
		return -1;
	}

	bg.setTexture(bgTexture);
	//bg.setOrigin(bgTexture.getSize().x/2, bgTexture.getSize().y/2);
	//bg.setScale(windWidth / bgTexture.getSize().x, windHeight / bgTexture.getSize().y);

	std::cout << (mainLvl.getLevelJSON()) << std::endl;
	Output::log(mainLvl.getLevelPath());
	Output::log(mainLvl.getAudioPath());

	/*
	print("WIDTH: " << windWidth << ", HEIGHT: " << windHeight);
	*/

	sf::Sprite plr;
	sf::Texture plrTexture;

	sf::Music lvlMusic;

	if (!plrTexture.loadFromFile("res/img/000.png"))
	{
		Output::error("Error occured while loading player texture file!");
		return -1;
	}

	float plrScale = 0.25f;
	sf::Vector2f plrScaleVec(plrScale, plrScale);

	plr.setOrigin(plrTexture.getSize().x / 2, plrTexture.getSize().y / 2);

	plr.setTexture(plrTexture);
	plr.setColor(sf::Color::Green);
	plr.setScale(plrScaleVec);
	plr.setPosition(sf::Vector2f(plrTexture.getSize().x, windHeight - plrTexture.getSize().y));

	while (window.isOpen())
	{
		sf::Event e;

		window.clear(sf::Color::White);
		window.draw(bg);
		window.draw(plr);
		mainLvl.update(window);
		window.display();

		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				Output::log("New WIDTH: " + std::to_string(e.size.width) + ", New HEIGHT: " + std::to_string(e.size.height));
				break;

			case sf::Event::LostFocus:
				// Pause game
				break;

			case sf::Event::GainedFocus:
				// Resume game
				break;

			case sf::Event::MouseButtonPressed:
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					// Left click
					break;
				}
			}

			case sf::Event::KeyPressed:
			{
				if (e.key.code == sf::Keyboard::Escape)
				{
					window.close();
					break;
				}
			}
			default:
				break;
			}
		}
	}

	return 0;
}