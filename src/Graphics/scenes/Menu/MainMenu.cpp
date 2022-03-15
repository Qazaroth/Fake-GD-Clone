#include "MainMenu.h"

// Private
void MainMenu::setup()
{
	Configs config;

	if (!_bgMusic.openFromFile(config.getMenuBGMusicPath()))
	{
		std::cout << "[ERROR] An error occured while loading audio file!" << std::endl;
		return;
	}

	_bgMusic.setLoop(true);
	_bgMusic.setVolume(18.75f);

	_title.setPosition((_windowSize.x / 2) - 10, _title.getPosition().y + 150);
	_playBtn.setPosition(_windowSize.x / 2, _windowSize.y / 2);
	
	float x = (_windowSize.x / _bg.getSprite().getLocalBounds().width) * 2; //(_bg.getTexture().getSize().x / _windowSize.x) / 2;
	float y = (_windowSize.y / _bg.getSprite().getLocalBounds().height) * 2;
	std::cout << x << std::endl;
	std::cout << y << std::endl;
	_bg.setScale(x, y);
}
// Public
MainMenu::MainMenu(sf::Vector2u windowSize) : _windowSize(windowSize)
{;
	setup();
}

MainMenu::~MainMenu() {}

void MainMenu::update(sf::RenderWindow &window)
{
	sf::Vector2i m = sf::Mouse::getPosition();

	if (_playBtn.isMouseOnBtn(m, window))
	{
		_playBtn.setScale(1.25f);
	}
	else
	{
		_playBtn.resetScale();
	}
}

void MainMenu::playBGM()
{
	if (_bgMusic.getStatus() == sf::SoundSource::Stopped || _bgMusic.getStatus() == sf::SoundSource::Paused)
		_bgMusic.play();
}

void MainMenu::stopBGM()
{
	_bgMusic.stop();
}

void MainMenu::pauseBGM()
{
	_bgMusic.pause();
}

void MainMenu::draw(sf::RenderWindow &window)
{
	window.draw(_bg.getSprite());
	window.draw(_title.getSprite());
	window.draw(_playBtn.getSprite());
}