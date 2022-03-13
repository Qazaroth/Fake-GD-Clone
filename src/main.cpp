#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "utils/Output.h"
#include "utils/Timer.h"
#include "Level/Level.h"

#include "Game.h"

#include "entity/Player.h"

#define defaultHeight 1080
#define defaultWidth 1920

#define jumpForce -50.0f

#define floorHeight 100.0f
#define floorWidth 2560.0f

std::string VERSION = "1.2.0-Beta";

int main()
{
	using namespace utils;

	Game game;

	sf::RenderWindow window(sf::VideoMode(defaultWidth, defaultHeight), "Fake GD Clone [" + VERSION + "]", sf::Style::Default);
	window.setFramerateLimit(game.getFPSCap());

	sf::Vector2u windowSize = window.getSize();

	Level mainLvl("res/data/levels/0.json", windowSize);

	unsigned int windWidth = windowSize.x;
	unsigned int windHeight = windowSize.y;

	Player plr("res/img/000.png", 0.25f, window);

	sf::Font fpsFont;
	sf::Text fpsTxt;

	if (!fpsFont.loadFromFile("res/fonts/arial.ttf"))
	{
		std::cout << "[ERROR] Error occured while loading font file!" << std::endl;
		return -1;
	}

	fpsTxt.setFont(fpsFont);
	fpsTxt.setCharacterSize(24);
	fpsTxt.setString("0 FPS");

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (window.isOpen())
	{
		if (game.isEnded()) return -1;

		sf::Event e;

		windowSize = window.getSize();
		windWidth = windowSize.x;
		windHeight = windowSize.y;

		//sf::Vector2i m = sf::Mouse::getPosition(window);

		//std::cout << "X: " << m.x << ", Y: " << m.y << std::endl;
		//std::cout << (plrTexture.getSize().y * plr.getScale().y) << std::endl;

		window.clear(sf::Color::White);
		mainLvl.update(window, plr, game);
		window.draw(fpsTxt);
		plr.update(window, frames, game.isPaused());
		window.display();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			if (frames < 60)
			{
				fpsTxt.setFillColor(sf::Color(255, 0, 0));
			}
			else if (frames >= 60 && frames < 120)
			{
				fpsTxt.setFillColor(sf::Color(0, 255, 0));
			}
			else
			{
				fpsTxt.setFillColor(sf::Color(255, 215, 0));
			}

			fpsTxt.setString(std::to_string(frames) + " FPS");
			//printf("%d FPS\n", frames);
			frames = 0;
		}

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
				game.setPause(true);
				break;

			case sf::Event::GainedFocus:
				game.setPause(false);
				break;

			case sf::Event::MouseButtonPressed:
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					plr.jump();
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
				else if (e.key.code == sf::Keyboard::Space)
				{
					plr.jump();
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