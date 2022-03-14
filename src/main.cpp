#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "utils/Output.h"
#include "utils/Timer.h"
#include "Level/Level.h"

#include "Game.h"
#include "configs.h"

#include "Graphics/Button.h"
#include "Graphics/Text.h"
#include "Graphics/Image.h"

#include "entity/Player.h"

#define defaultHeight 1080
#define defaultWidth 1920

#define jumpForce -50.0f

#define floorHeight 100.0f
#define floorWidth 2560.0f

std::string VERSION = "1.3.0-Beta";

int main()
{
	Configs config;
	Game game;

	sf::Music _mmBGMusic;

	if (!_mmBGMusic.openFromFile(config.getMenuBGMusicPath()))
	{
		Output::error("An error occured while loading audio file!");
		return -1;
	}

	_mmBGMusic.setLoop(true);
	_mmBGMusic.setVolume(18.75f);
	
	Image bg("res/img/bg1.png", true);
	Button playBtn("res/img/play.png");
	Image title("res/img/title.png");

	//bg.setColor(sf::Color::Green);
	bg.getSprite().setTextureRect(sf::IntRect(bg.getTexture().getSize().x-2044, 0, 2043, 2043));

	Text fpsText("res/fonts/arial.ttf", "0 FPS");
	fpsText.setCharacterSize(24);

	sf::RenderWindow window(sf::VideoMode(defaultWidth, defaultHeight), "Fake GD Clone [" + VERSION + "]", sf::Style::Default);
	//window.setFramerateLimit(config.getFPSCap());
	window.setVerticalSyncEnabled(true);

	title.setPosition((window.getSize().x / 2) - 10, title.getPosition().y + 150);
	playBtn.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	//_mmBG.setScale(sf::Vector2f(window.getSize().x / _mmBGTexture.getSize().x, window.getSize().y / _mmBGTexture.getSize().y));

	utils::Timer time;
	float timer = 0;
	unsigned int frames = 0;
	_mmBGMusic.play();
	while (window.isOpen())
	{		
		sf::Event e;
		sf::Vector2i m = sf::Mouse::getPosition(window);

		if (playBtn.isMouseOnBtn(m, window))
		{
			playBtn.setScale(1.25f);
		}
		else
		{
			playBtn.resetScale();
		}

		window.clear(sf::Color::White);
		window.draw(bg.getSprite());

		if (game.showFPS()) window.draw(fpsText.getSFText());

		window.draw(title.getSprite());
		window.draw(playBtn.getSprite());
		window.display();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			if (game.showFPS())
			{
				if (frames < 60)
				{
					fpsText.setFillColor(sf::Color(255, 0, 0));
				}
				else if (frames >= 60 && frames < 120)
				{
					fpsText.setFillColor(sf::Color(0, 255, 0));
				}
				else
				{
					fpsText.setFillColor(sf::Color(255, 215, 0));
				}

				fpsText.setText(std::to_string(frames) + " FPS");
			}
			printf("%d FPS\n", frames);
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
				break;

			case sf::Event::GainedFocus:
				break;

			case sf::Event::MouseButtonPressed:
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					if (playBtn.isMouseOnBtn(m, window))
					{
						std::cout << playBtn.isMouseOnBtn(m, window) << std::endl;
					}
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
					break;
				}
				else if (e.key.code == sf::Keyboard::F3)
				{
					game.toggleFPSCounter();
					break;
				}
			}
			default:
				break;
			}
		}
	}

	/*
	sf::Vector2u windowSize = window.getSize();

	Level mainLvl("res/data/levels/0.json", windowSize);

	unsigned int windWidth = windowSize.x;
	unsigned int windHeight = windowSize.y;

	Player plr("res/img/000.png", 0.25f, window);

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
	*/

	return 0;
}