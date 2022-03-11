#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "utils/Timer.h"

#define print(x) std::cout << x << std::endl

float _timer = 0.0f;
float _updateTimer = 0.0f;
float updateTick = 1.0f / 60.0f;

unsigned int updates = 0;
unsigned int frames = 0;
unsigned int fpsInt = 0;
unsigned int upsInt = 0;

int main()
{
	utils::Timer timer;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Fake GD Clone");
	sf::Vector2u windowSize = window.getSize();

	unsigned int windWidth = windowSize.x;
	unsigned int windHeight = windowSize.y;

	/*
	print("WIDTH: " << windWidth << ", HEIGHT: " << windHeight);
	*/

	sf::Sprite plr;
	sf::Texture plrTexture;

	sf::Font font;
	sf::Text fps;

	sf::Music lvlMusic;

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

	if (!lvlMusic.openFromFile("res/audio/0.ogg"))
	{
		print("Error occured while loading audio file!");
		return -1;
	}

	float plrScale = 0.25f;
	sf::Vector2f plrScaleVec(plrScale, plrScale);

	plr.setOrigin(plrTexture.getSize().x / 2, plrTexture.getSize().y / 2);

	plr.setTexture(plrTexture);
	plr.setColor(sf::Color::Green);
	plr.setScale(plrScaleVec);
	plr.setPosition(sf::Vector2f(plrTexture.getSize().x, windHeight - plrTexture.getSize().y));

	fps.setFont(font);
	fps.setCharacterSize(24);
	fps.setString("0 FPS");

	lvlMusic.setVolume(50.0f);
	lvlMusic.play();

	while (window.isOpen())
	{
		sf::Event e;
		
		frames++;
		window.clear();
		window.draw(plr);
		//window.draw(fps);
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

		/*
		if (fpsInt >= 120)
		{
			fps.setFillColor(sf::Color(255, 215, 0));
		}
		else if (fpsInt >= 60 && fpsInt < 120)
		{
			fps.setFillColor(sf::Color(0, 255, 0));
		}
		else
		{
			fps.setFillColor(sf::Color(255, 0, 0));
		}

		fps.setString(std::to_string(fpsInt) + " FPS");
		*/
		if (timer.elapsed() - _timer > 1.0f)
		{
			_timer += 1.0f;
			fpsInt = frames;
			upsInt = updates;
			frames = 0;
			updates = 0;
			print(fpsInt << " FPS");
			timer.reset();
		}
	}

	return 0;
}