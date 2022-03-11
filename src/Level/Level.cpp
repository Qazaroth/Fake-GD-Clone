#include "Level.h"

//Private
void Level::setup()
{
	_IsInit = false;
	if (_levelPath == "" && _audioPath == "")
	{
		std::cout << "[ERROR] Unable to load a level due to missing arguments!" << std::endl;
		return;
	}

	if (!_bgMusic.openFromFile(_audioPath))
	{
		std::cout << "[ERROR] An error occured while loading audio file!" << std::endl;
		return;
	}

	_lvlData = FileUtils::readFile(_levelPath);

	if (_lvlData.empty() || _lvlData == ERRSTRING)
	{
		std::cout << "[ERROR] An error occured while loading level data!" << std::endl;
		return;
	}

	_IsInit = true;
	_lvlJson = nlohmann::json::parse(_lvlData);
	std::cout << "[SUCCESS] Succesfully loaded level!" << std::endl;
}
//Public
Level::Level(std::string levelPath, std::string audioPath)
{
	_levelPath = levelPath;
	_audioPath = audioPath;

	setup();
}

Level::~Level() {}