#pragma once

#include "../utils/FileUtils.h"

#include <nlohmann/json.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

class Level
{
private:
	bool _IsInit = false;

	unsigned int _lvlTimer = 0; // Helps to keep track of when to place object(s)

	std::string _levelPath = "";
	std::string _audioPath = "";
	
	std::string _lvlData = "";
	nlohmann::json _lvlJson;
	sf::Music _bgMusic;

	void setup();
public:
	Level(std::string levelPath, std::string audioPath);
	~Level();

	inline nlohmann::json getLevelJSON() { return _lvlJson; }

	inline std::string getLevelPath() { return _levelPath; }
	inline std::string getAudioPath() { return _audioPath; }
	inline std::string getLevelData() { return _lvlData; }
};