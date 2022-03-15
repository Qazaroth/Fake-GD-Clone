#include "MainMenu.h"

// Private
void MainMenu::setup()
{
	Configs config;
	srand(time(NULL));
	
	int s = 1 + (std::rand() % (20 - 1 + 1));
	std::string imgPath = "";

	if (s < 10) imgPath = "res/img/game_bg_0" + std::to_string(s) + "_001-uhd.png";
	else imgPath = "res/img/game_bg_" + std::to_string(s) + "_001-uhd.png";
	//_bg = Image("res/img/game_bg_01_001.png", true, true);

	if (!_bgTexture.loadFromFile(imgPath))
	{
		std::cout << "Error occured while loading background file!" << std::endl;
		return;
	}

	int min = 0;
	int max = 255;

	int r = min + (std::rand() % (max - min + 1));
	int g = min + (std::rand() % (max - min + 1));
	int b = min + (std::rand() % (max - min + 1));

	_bg.setColor(sf::Color(r, g, b));

	_bg.setOrigin(_bgTexture.getSize().x / 2, _bgTexture.getSize().y / 2);
	_bg.setTexture(_bgTexture);

	if (!_bgMusic.openFromFile(config.getMenuBGMusicPath()))
	{
		std::cout << "[ERROR] An error occured while loading audio file!" << std::endl;
		return;
	}

	_bgMusic.setLoop(true);
	_bgMusic.setVolume(18.75f);

	_title.setPosition((_windowSize.x / 2) - 10, _title.getPosition().y + 150);
	_playBtn.setPosition(_windowSize.x / 2, _windowSize.y / 2);
	_bg.setPosition(_windowSize.x / 2, _windowSize.y / 2);
	
	//float yOff = (512.0f / _bg.getTexture().getSize().y);
	float x = (_windowSize.x / _bg.getLocalBounds().width);// *2; //(_bg.getTexture().getSize().x / _windowSize.x) / 2;
	float y = (_windowSize.y / _bg.getLocalBounds().height);// *2;

	if (x < 1.0f) x = 1.0f;
	if (y < 1.0f) y = 1.0f;

	_bg.setScale(x, y);
	//_bg.setPosition(_windowSize.x / 2, _windowSize.y / 2);
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
	window.draw(_bg);
	window.draw(_title.getSprite());
	window.draw(_playBtn.getSprite());
}