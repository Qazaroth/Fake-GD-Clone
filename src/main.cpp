#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "utils/Timer.h"
#include "Level/Level.h"

#define print(x) std::cout << x << std::endl

int main()
{
	Level mainLvl("src/Data/Lvls/0.json", "res/audio/0.ogg");

	sf::RenderWindow window(sf::VideoMode(800, 600), "Fake GD Clone");
	sf::Vector2u windowSize = window.getSize();

	unsigned int windWidth = windowSize.x;
	unsigned int windHeight = windowSize.y;

	print(mainLvl.getLevelJSON());
	print(mainLvl.getLevelPath());
	print(mainLvl.getAudioPath());
	print(mainLvl.getLevelData());

	/*
	print("WIDTH: " << windWidth << ", HEIGHT: " << windHeight);
	*/

	sf::Sprite plr;
	sf::Texture plrTexture;

	sf::Music lvlMusic;

	if (!plrTexture.loadFromFile("res/000.png"))
	{
		print("Error occured while loading player texture file!");
		return -1;
	}

	/*
	if (!lvlMusic.openFromFile("res/audio/0.ogg"))
	{
		print("Error occured while loading audio file!");
		return -1;
	}
	*/

	float plrScale = 0.25f;
	sf::Vector2f plrScaleVec(plrScale, plrScale);

	plr.setOrigin(plrTexture.getSize().x / 2, plrTexture.getSize().y / 2);

	plr.setTexture(plrTexture);
	plr.setColor(sf::Color::Green);
	plr.setScale(plrScaleVec);
	plr.setPosition(sf::Vector2f(plrTexture.getSize().x, windHeight - plrTexture.getSize().y));

	//lvlMusic.setVolume(50.0f);
	//lvlMusic.play();

	while (window.isOpen())
	{
		sf::Event e;

		window.clear();
		window.draw(plr);
		window.display();

		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				print("New WIDTH: " << e.size.width << ", New HEIGHT: " << e.size.height);
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
			default:
				break;
			}
		}
	}

	return 0;
}