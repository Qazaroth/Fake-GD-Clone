#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// 1 to use SF
// 0 to use utils/Timer
#define ALTERNATE_FPS 1

#if ALTERNATE_FPS == 0
#include "utils/Timer.h"
#endif

#define print(x) std::cout << x << std::endl

float _timer = 0.0f;

unsigned int frames = 0;

int main()
{
	sf::Clock clock;
#if ALTERNATE_FPS == 1
	sf::Time timer;
#else
	utils::Timer timer;
#endif

	sf::Window window(sf::VideoMode(800, 600), "Fake GD Clone");

	sf::Vector2u windowSize = window.getSize();
	unsigned int windWidth = windowSize.x;
	unsigned int windHeight = windowSize.y;

	print("WIDTH: " << windWidth << ", HEIGHT: " << windHeight);

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

			default:
				break;
			}
		}
		
#if ALTERNATE_FPS == 1
		timer = clock.getElapsedTime();
		if (timer.asSeconds() - _timer > 1.0f)
		{
			_timer += 1.0f;
			print(frames << " FPS");
			frames = 0;
		}
#else
		if (timer.elapsed() - _timer > 1.0f) 
		{
			_timer += 1.0f;
			print(frames << " FPS");
			timer.reset();
			frames = 0;
		}
#endif
	}

	return 0;
}