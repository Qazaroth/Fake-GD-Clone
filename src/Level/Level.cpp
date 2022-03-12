#include "Level.h"

//Private
void Level::setup()
{
	Configs config;
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

	if (!_bgTexture.loadFromFile(_bgPath))
	{
		Output::error("Error occured while loading background file!");
		return;
	}

	_background.setTexture(_bgTexture);

	_bgMusic.setVolume(37.5f);

	_floor.setSize(config.getFloorSize());
	_floor.setFillColor(sf::Color::Black);
	_floor.setPosition(sf::Vector2f(0.0f, _windowSize.y - (_floor.getSize().y)));

	for (auto i : _objsArr.items())
	{
		auto key = i.key();
		auto val = i.value();

		int type = val["type"];
		int posT = val["pos_T"];
		int posY = val["pos_Y"];

		std::list<int> values;

		values.push_back(type);
		values.push_back(posT);
		values.push_back(posY);

		_objects.insert(std::pair<int, std::list<int>>(posT, values));

		//std::cout << "[" << key << "] " << val << std::endl;
	}

	Output::log("Succesfully loaded level!");
	_IsInit = true;
}

int Level::getDataOfObject(std::list<int> values, int index)
{
	using namespace std;

	auto i = values.begin();

	advance(i, index);

	return *i;
}
//Public
Level::Level(std::string levelPath, sf::Vector2u windowSize)
{
	_levelPath = levelPath;
	_windowSize = windowSize;

	setup();
}

Level::~Level() {}

void Level::update(sf::RenderWindow &window, bool isPaused)
{
	if (_IsInit)
	{
		window.draw(_background);

		_windowSize = window.getSize();

		if (!isPaused)
		{
			_lvlTimer++;
			if (_bgMusic.getStatus() == sf::SoundSource::Playing)
			{
				_lvlTimer++;
			}
			else
			{
				//_bgMusic.play();
			}

			if (_renderBlocks.size() > 0)
			{
				for (int i = 0; i < _renderBlocks.size(); i++)
				{
					std::list<Objects::Block>::iterator e = _renderBlocks.begin();
					std::advance(e, i);

					window.draw((*e).getObject());
				}
			}
			

			if (_objects.count(_lvlTimer))
			{
				auto obj = _objects.find(_lvlTimer);

				int type = getDataOfObject(obj->second, 0);
				int posT = getDataOfObject(obj->second, 1);
				int posY = getDataOfObject(obj->second, 2);

				if (type == 1)
				{
					Objects::Block block(_windowSize.x - 100, posY, _windowSize);
					_renderBlocks.push_back(block);
					window.draw(block.getObject());
				}
				
				//std::cout << type << " | " << posT << ", " << posY << std::endl;
			}
		}

		window.draw(_floor);
	}
}