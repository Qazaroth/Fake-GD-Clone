#include "Level.h"

//Private
void Level::setup()
{
	_IsInit = false;
	if (_levelPath == "")
	{
		std::cout << "[ERROR] Unable to load a level due to missing arguments!" << std::endl;
		return;
	}

	_lvlData = FileUtils::readFile(_levelPath);

	if (_lvlData.empty() || _lvlData == ERRSTRING)
	{
		std::cout << "[ERROR] An error occured while loading level data!" << std::endl;
		return;
	}
	_lvlJson = nlohmann::json::parse(_lvlData);

	_lvlName = _lvlJson["name"];
	_audioPath = _lvlJson["audio"];

	if (!_bgMusic.openFromFile(_audioPath))
	{
		std::cout << "[ERROR] An error occured while loading audio file!" << std::endl;
		return;
	}

	_bgMusic.setVolume(37.5f);

	std::cout << "[SUCCESS] Succesfully loaded level!" << std::endl;
	_IsInit = true;
}
//Public
Level::Level(std::string levelPath)
{
	_levelPath = levelPath;

	setup();
}

Level::~Level() {}

void Level::update()
{
	if (_IsInit)
	{
		if (_bgMusic.getStatus() == sf::SoundSource::Playing)
		{
			_lvlTimer += 1;
		}
		else
		{
			_bgMusic.play();
		}
	}
}