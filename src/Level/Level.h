#pragma once

#include "../utils/FileUtils.h"

#include <nlohmann/json.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

enum class ObjectType
{
	BLOCK = 0
};

class Level
{
protected:
	std::string _lvlData = "";

	bool _IsInit = false;

	unsigned int _lvlTimer = 0; // Helps to keep track of when to place object(s)
private:
	std::string _levelPath = "";
	std::string _audioPath = "";
	std::string _bgPath = "";
	
	std::string _lvlName = "";
	nlohmann::json _lvlJson;
	sf::Music _bgMusic;

	void setup();
public:
	Level(std::string levelPath);
	~Level();

	void update(sf::RenderWindow &window);

	inline nlohmann::json getLevelJSON() { return _lvlJson; }

	inline int getLevelTick() { return _lvlTimer; }

	inline std::string getLevelName() { return _lvlName; }
	inline std::string getLevelBG() { return _bgPath; }
	inline std::string getLevelPath() { return _levelPath; }
	inline std::string getAudioPath() { return _audioPath; }
	inline std::string getLevelData() { return _lvlData; }
};