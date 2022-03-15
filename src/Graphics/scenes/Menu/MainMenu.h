#pragma once

#include "../../Button.h"
#include "../../Image.h"
#include "../../Text.h"

#include "../../../configs.h"

#include <iostream>
#include <time.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class MainMenu
{
private:
	sf::Music _bgMusic;

	sf::Vector2u _windowSize;

	//Image _bg;//Image("res/img/bg1.png", true);
	sf::Sprite _bg;
	sf::Texture _bgTexture;

	Image _title = Image("res/img/title.png");
	Button _playBtn = Button("res/img/play.png");

	void setup();
public:
	MainMenu(sf::Vector2u windowSize);
	~MainMenu();

	void update(sf::RenderWindow &window);

	void playBGM();
	void stopBGM();
	void pauseBGM();

	void draw(sf::RenderWindow &window);

	inline sf::SoundSource::Status getMusicStatus() { return _bgMusic.getStatus(); }

	inline Button getPlayBtn() { return _playBtn; }
};