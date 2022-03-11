#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "utils/Output.h"
#include "utils/Timer.h"
#include "Level/Level.h"

#include "entity/Player.h"

#define defaultHeight 1080
#define defaultWidth 1920

#define floorHeight 100.0f
#define floorWidth 2560.0f

int main()
{
	bool isPaused = false;

	Level mainLvl("res/data/levels/0.json");

	sf::RenderWindow window(sf::VideoMode(defaultWidth, defaultHeight), "Fake GD Clone", sf::Style::Default);
	sf::Vector2u windowSize = window.getSize();

	unsigned int windWidth = windowSize.x;
	unsigned int windHeight = windowSize.y;

	sf::RectangleShape floor;

	floor.setSize(sf::Vector2f(floorWidth, floorHeight));
	floor.setFillColor(sf::Color::Black);
	floor.setPosition(sf::Vector2f(0.0f, windHeight - (floor.getSize().y)));

	sf::Sprite bg;
	sf::Texture bgTexture;

	if (!bgTexture.loadFromFile(mainLvl.getLevelBG()))
	{
		Output::error("Error occured while loading background file!");
		return -1;
	}

	bg.setTexture(bgTexture);

	Player player("res/img/000.png", 0.25f);

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

	int plrOffsetX = 5;
	int plrOffsetY = 39;

	float plrDefaultPosX = plrOffsetX + ((plrTexture.getSize().x * plrScale) / 2);
	float plrDefaultPosY = (windHeight - floor.getSize().y) - (plrTexture.getSize().y * plrScale) + plrOffsetY;// + windHeight - plrOffsetY - (plrTexture.getSize().y * plrScale);

	sf::Vector2f plrDefaultPos(plrDefaultPosX, plrDefaultPosY);

	plr.setPosition(plrDefaultPos);

	sf::Vector2f velocity(5.0f, 0.0f);

	while (window.isOpen())
	{
		windowSize = window.getSize();

		windWidth = windowSize.x;
		windHeight = windowSize.y;

		sf::Vector2i m = sf::Mouse::getPosition(window);
		sf::Event e;

		//std::cout << "X: " << m.x << ", Y: " << m.y << std::endl;
		//std::cout << (plrTexture.getSize().y * plr.getScale().y) << std::endl;

		//float maxY = windHeight - (plrTexture.getSize().y * plr.getScale().y / (10 / plr.getScale().y));
		float maxY = (defaultHeight - ((30/ defaultHeight) * windHeight)) - ((plrTexture.getSize().y * plr.getScale().y) / 2);
		//std::cout << maxY << std::endl;
		float maxX = (defaultWidth - ((30/ defaultWidth) * windWidth)) - ((plrTexture.getSize().x * plr.getScale().x) / 2); //windWidth - (plrTexture.getSize().x * plr.getScale().x);
		float minX = (plrTexture.getSize().x * plr.getScale().x) - 30;
		float minY = (plrTexture.getSize().y * plr.getScale().y) - 30;

		if (!isPaused)
		{
			plr.move(velocity);
		}
		

		if (plr.getPosition().y < minY)
		{
			plr.setPosition(plr.getPosition().x, minY);
		}
		else if (plr.getPosition().y > maxY)
		{
			plr.setPosition(plr.getPosition().x, maxY);
		}

		if (plr.getPosition().x < minX)
		{
			velocity.x = 5.0f;//(5.0f/defaultWidth) * windWidth;
		}
		else if (plr.getPosition().x > maxX)
		{
			velocity.x = -5.0f;//((5.0f / defaultWidth) * windWidth);
		}

		if (plr.getPosition().y < plrDefaultPosY)
		{
			plr.move(0.0f, 1.25f);
		}

		window.clear(sf::Color::White);
		window.draw(bg);
		window.draw(floor);
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
			{
				if (e.size.width < 960)
				{
					e.size.width = 960;
					window.setSize(sf::Vector2u(960, window.getSize().y));
				}

				if (e.size.height < 540)
				{
					e.size.height = 540;
					window.setSize(sf::Vector2u(window.getSize().x, 540));
				}

				if (e.size.width > 2560)
				{
					e.size.width = 2560;
					window.setSize(sf::Vector2u(2560, window.getSize().y));
				}

				if (e.size.height > 1440)
				{
					e.size.height = 1440;
					window.setSize(sf::Vector2u(window.getSize().x, 1440));
				}

				Output::log("New WIDTH: " + std::to_string(e.size.width) + ", New HEIGHT: " + std::to_string(e.size.height));
				break;
			}

			case sf::Event::LostFocus:
				isPaused = true;
				// Pause game
				break;

			case sf::Event::GainedFocus:
				isPaused = false;
				// Resume game
				break;

			case sf::Event::MouseButtonPressed:
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					plr.move(sf::Vector2f(0.0f, -50.0f));
					// Left click
					break;
				}
				else if (e.mouseButton.button == sf::Mouse::Right)
				{
					plr.move(sf::Vector2f(0.0f, 50.0f));
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