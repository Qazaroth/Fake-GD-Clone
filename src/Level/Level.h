#pragma once

#include "../utils/FileUtils.h"
#include "../utils/Output.h"

#include "objects/Block.h"

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
	nlohmann::json _objsArr = nlohmann::json::array();

	bool _IsInit = false;

	unsigned int _lvlTimer = 0; // Helps to keep track of when to place object(s)
private:
	std::string _levelPath = "";
	std::string _audioPath = "";
	std::string _bgPath = "";
	
	std::string _lvlName = "";
	nlohmann::json _lvlJson;
	sf::Music _bgMusic;

	sf::RectangleShape _floor;

	void setup();
public:
	Level(std::string levelPath);
	~Level();

	void update(sf::RenderWindow &window);

	inline nlohmann::json getLevelJSON() { return _lvlJson; }
	inline nlohmann::json getObjects() { return _objsArr; }

	inline int getLevelTick() { return _lvlTimer; }

	inline sf::RectangleShape getFloor() { return _floor; }

	inline std::string getLevelName() { return _lvlName; }
	inline std::string getLevelBG() { return _bgPath; }
	inline std::string getLevelPath() { return _levelPath; }
	inline std::string getAudioPath() { return _audioPath; }
	inline std::string getLevelData() { return _lvlData; }
};