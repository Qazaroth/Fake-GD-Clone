#include "Level.h"

//Private
void Level::setup()
{
	_IsInit = false;
	if (_levelPath == "")
	{
		Output::error("Unable to load a level due to missing arguments!");
		return;
	}

	_lvlData = FileUtils::readFile(_levelPath);

	if (_lvlData.empty() || _lvlData == ERRSTRING)
	{
		Output::error("An error occured while loading level data!");
		return;
	}
	_lvlJson = nlohmann::json::parse(_lvlData);

	_lvlName = _lvlJson["name"];
	_audioPath = _lvlJson["audio"];
	_bgPath = _lvlJson["bg"];
	_objsArr = _lvlJson["objects"];

	if (!_bgMusic.openFromFile(_audioPath))
	{
		Output::error("An error occured while loading audio file!");
		return;
	}

	_bgMusic.setVolume(37.5f);

	Output::log("Succesfully loaded level!");
	_IsInit = true;
}
//Public
Level::Level(std::string levelPath)
{
	_levelPath = levelPath;

	setup();
}

Level::~Level() {}

void Level::update(sf::RenderWindow &window)
{
	if (_IsInit)
	{
		if (_bgMusic.getStatus() == sf::SoundSource::Playing)
		{
			_lvlTimer += 1;
		}
		else
		{
			//_bgMusic.play();
		}

		for (auto i : _objsArr.items())
		{
			auto key = i.key();
			auto val = i.value();

			auto type = val["type"];
			auto posT = val["pos_T"];
			auto posX = val["pos_X"];
			auto posY = val["pos_Y"];

			if (_lvlTimer == posT)
			{
				using namespace Objects;

				sf::RectangleShape rect(sf::Vector2f(10.0f, 10.0f));
				rect.setPosition(50, 50);
				rect.setFillColor(sf::Color::Black);

				Block block(posX, posY, window.getSize());
				std::cout << "[" << key << "] " << val["type"] << std::endl;
				window.draw(rect);
			}
			
		}
	}
}