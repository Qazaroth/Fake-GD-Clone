#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "utils/Output.h"
#include "utils/Timer.h"
#include "Level/Level.h"

#include "Graphics/scenes/Menu/MainMenu.h"

#include "Game.h"
#include "configs.h"

#include "Graphics/Button.h"
#include "Graphics/Text.h"
#include "Graphics/Image.h"

#include "entity/Player.h"

#define defaultHeight 1080
#define defaultWidth 1920

std::string VERSION = "2.1.0-Beta";
std::string TITLE = "Fake GD Clone [" + VERSION + "]";
sf::VideoMode windowDimension(defaultWidth, defaultHeight);

Configs config;
Game game;
utils::Timer timer;
Text fpsText("res/fonts/arial.ttf", "0 FPS");

std::vector<sf::VideoMode> VModes = sf::VideoMode::getFullscreenModes();

float timerCounter = 0;
unsigned int frames = 0;

void resizeHandler(sf::Event e, sf::RenderWindow &window)
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
}

int main()
{
	fpsText.setCharacterSize(24);
	sf::Uint32 mStyleFlag = sf::Style::Default | sf::Style::Fullscreen;
	sf::RenderWindow window(VModes.at(0), TITLE, mStyleFlag); //window(windowDimension, TITLE, sf::Style::Default);
	window.setFramerateLimit(config.getFPSCap());

	sf::Vector2u windowSize = window.getSize();

	Level mainLvl("res/data/levels/0.json", windowSize);
	MainMenu mainMenu(window.getSize());

	unsigned int windWidth = windowSize.x;
	unsigned int windHeight = windowSize.y;

	Player plr("res/img/000.png", 0.25f, window);

	while (window.isOpen())
	{		
		if (game.isEnded()) return -1;

		sf::Event e;
		sf::Vector2i m = sf::Mouse::getPosition(window);

		GameState gameState = game.getGameState();

		switch (gameState)
		{
		case GameState::IN_MAINMENU:
			mainLvl.stopBGMusic();
			mainMenu.playBGM();
			mainMenu.update(window);
			break;
		case GameState::IN_LEVEL:
			mainMenu.stopBGM();
			plr.update(window, frames, game);
			break;
		default:
			mainMenu.update(window);
			break;
		}
		

		window.clear(sf::Color::White);
		switch (gameState)
		{
		case GameState::IN_MAINMENU:
			mainMenu.draw(window);
			break;
		case GameState::IN_LEVEL:
			mainLvl.update(window, plr, game);
			plr.draw(window);
			break;
		default:
			mainMenu.draw(window);
			break;
		}
		if (game.showFPS()) window.draw(fpsText.getSFText());
		window.display();

		frames++;
		if (timer.elapsed() - timerCounter > 1.0f)
		{
			timerCounter += 1.0f;
			if (game.showFPS()) fpsText.setText(std::to_string(frames) + " FPS");
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
				resizeHandler(e, window);

				break;
			}

			case sf::Event::LostFocus:
				if (gameState != GameState::IN_MAINMENU) game.setPause(true);
				break;

			case sf::Event::GainedFocus:
				if (gameState != GameState::IN_MAINMENU) game.setPause(false);
				break;

			case sf::Event::MouseButtonPressed:
			{
				switch (gameState)
				{
				case GameState::IN_MAINMENU:
				{
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						if (mainMenu.getPlayBtn().isMouseOnBtn(m, window))
						{
							//std::cout << mainMenu.getPlayBtn().isMouseOnBtn(m, window) << std::endl;
							game.setGameState(GameState::IN_LEVEL);
						}
						break;
					}
					break;
				}
				case GameState::IN_LEVEL:
				{
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						plr.jump();
						break;
					}
				}
				default:
					break;
				}
				
			}

			case sf::Event::KeyPressed:
			{
				if (e.key.code == sf::Keyboard::Escape)
				{
					switch (gameState)
					{
					case GameState::IN_LEVEL:
						game.setGameState(GameState::IN_MAINMENU);
						break;
					case GameState::IN_MAINMENU:
					default:
						window.close();
						break;
					}
					
				}
				else if (e.key.code == sf::Keyboard::Space)
				{
					if (gameState == GameState::IN_LEVEL)
					{
						if (e.mouseButton.button == sf::Mouse::Left)
						{
							plr.jump();
							break;
						}
					}
				}
				else if (e.key.code == sf::Keyboard::F3)
				{
					game.toggleFPSCounter();
					break;
				}
				break;
			}
			default:
				break;
			}
		}
	}

	/*
	while (window.isOpen())
	{
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
	}
	*/

	return 0;
}
