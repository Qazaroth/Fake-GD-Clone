#pragma once

#include "../utils/FileUtils.h"
#include "../utils/Output.h"

#include "../configs.h"
#include "../Game.h"

#include "../Graphics/Image.h"

#include "objects/Block.h"
#include "../entity/Player.h"

#include <nlohmann/json.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <map>
#include <iterator>
#include <typeinfo>

enum class ObjectType
{
	BLOCK = 0
};

class Level
{
protected:
	std::string _lvlData = "";
	nlohmann::json _objsArr = nlohmann::json::array();

	sf::Vector2u _windowSize;
	std::map<int, std::list<std::string>> _objects;
	std::list<Objects::Block> _renderBlocks;

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
	sf::Sprite _background;
	sf::Texture _bgTexture;

	void setup();

	std::string getDataOfObject(std::list<std::string> values, int index);
public:
	Level(std::string levelPath, sf::Vector2u windowSize);
	~Level();

	void resetLevel();

	void stopBGMusic();

	void update(sf::RenderWindow &window, Player &plr, Game &game);

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