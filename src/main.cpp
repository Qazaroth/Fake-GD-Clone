#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// 1 to use SF
// 0 to use utils/Timer
#define ALTERNATE_FPS 2

#include "utils/Timer.h"

#define print(x) std::cout << x << std::endl

float _timer = 0.0f;
unsigned int frames = 0;

int main()
{
	utils::Timer timer;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Fake GD Clone");

	/*
	sf::Vector2u windowSize = window.getSize();
	unsigned int windWidth = windowSize.x;
	unsigned int windHeight = windowSize.y;

	print("WIDTH: " << windWidth << ", HEIGHT: " << windHeight);
	*/

	sf::Sprite plr;
	sf::Texture plrTexture;
	sf::Font font;
	sf::Text fps;

	if (!plrTexture.loadFromFile("res/000.png"))
	{
		print("Error occured while loading player texture file!");
		return -1;
	}

	if (!font.loadFromFile("res/fonts/arial.ttf"))
	{
		print("Error occured while loading font file!");
		return -1;
	}

	plr.setTexture(plrTexture);
	plr.setColor(sf::Color::Green);
	plr.setPosition(sf::Vector2f(window.getSize().x - plrTexture.getSize().x, window.getSize().y - plrTexture.getSize().y));

	fps.setFont(font);
	fps.setCharacterSize(24);
	fps.setString("0 FPS");

	while (window.isOpen())
	{
		sf::Event e;
		frames++;

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

		window.clear(sf::Color::Black);
		window.draw(plr);
		window.draw(fps);
		window.display();

		if (timer.elapsed() - _timer > 1.0f)
		{
			_timer += 1.0f;
			if (frames < 60)
			{
				fps.setFillColor(sf::Color(255, 0, 0));
			}
			else if (frames >= 60 && frames < 120)
			{
				fps.setFillColor(sf::Color(0, 255, 0));
			}
			else
			{
				fps.setFillColor(sf::Color(255, 215, 0));
			}

			fps.setString(std::to_string(frames) + " FPS");
			//print(frames << " FPS");
			timer.reset();
			frames = 0;
		}
	}

	return 0;
}