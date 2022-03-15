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

	_bgMusic.setVolume(18.75f);//37.5f);

	_floor.setSize(config.getFloorSize());
	_floor.setFillColor(sf::Color::Black);
	_floor.setPosition(sf::Vector2f(0.0f, _windowSize.y - (_floor.getSize().y)));

	for (auto i : _objsArr.items())
	{
		auto key = i.key();
		auto val = i.value();

		int type = val["type"];
		int posT = val["pos_T"];
		std::string posYStr;
		int posY = 0;
		bool isYRelative = false;
		
		try
		{ 
			posYStr = val["pos_Y"];
			std::transform(posYStr.begin(), posYStr.end(), posYStr.begin(), [](unsigned char c) { return std::tolower(c); });
			
			if (posYStr == "height")
			{
				posY = _windowSize.y - config.getFloorSize().y;
				isYRelative = true;
			}
		}
		catch (nlohmann::detail::type_error e) 
		{
			posY = val["pos_Y"];
			posYStr = std::to_string(posY);
		}

		std::list<std::string> values;

		values.push_back(std::to_string(type));
		values.push_back(std::to_string(posT));
		values.push_back(posYStr);
		values.push_back(std::to_string(posY));
		values.push_back(std::to_string(isYRelative));

		_objects.insert(std::pair<int, std::list<std::string>>(posT, values));

		//std::cout << "[" << key << "] " << val << std::endl;
	}

	Output::log("Succesfully loaded level!");
	_IsInit = true;
}

std::string Level::getDataOfObject(std::list<std::string> values, int index)
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

void Level::resetLevel()
{
	stopBGMusic();
}

void Level::stopBGMusic()
{
	_bgMusic.stop();
}

void Level::update(sf::RenderWindow &window, Player &plr, Game &game)
{
	Configs config;
	sf::FloatRect plrGlobalBounds = plr.getPlayer().getGlobalBounds();

	bool isMusicPlaying = _bgMusic.getStatus() == sf::SoundSource::Playing;

	if (_IsInit)
	{
		window.draw(_background);

		_windowSize = window.getSize();

		if (_renderBlocks.size() > 0)
		{
			for (int i = 0; i < _renderBlocks.size(); i++)
			{
				std::list<Objects::Block>::iterator e = _renderBlocks.begin();
				std::advance(e, i);

				Objects::Block b = (*e);
				//sf::Vector2f newPos(-b.getSize(), 0.0f);

				sf::FloatRect blockGlobalBounds = b.getObject().getGlobalBounds();

				//b.move(newPos);
				window.draw(b.getObject());
				if (plr.collideWith(b)) game.setEnded(true);
			}
		}

		if (!game.isPaused())
		{
			if (isMusicPlaying)
			{
				_lvlTimer++;

				if (_objects.count(_lvlTimer))
				{
					auto obj = _objects.find(_lvlTimer);

					int type = std::stoi(getDataOfObject(obj->second, 0));
					int posT = std::stoi(getDataOfObject(obj->second, 1));
					std::string posYStr = getDataOfObject(obj->second, 2);
					auto posY = std::stoi(getDataOfObject(obj->second, 3));
					std::string isYRelativeStr = getDataOfObject(obj->second, 4);
					bool isYRelative;

					// returns false on bad input
					std::istringstream(isYRelativeStr) >> isYRelative;

					if (isYRelative)
					{
						std::transform(posYStr.begin(), posYStr.end(), posYStr.begin(), [](unsigned char c) { return std::tolower(c); });

						if (posYStr == "height")
						{
							posY = _windowSize.y - config.getFloorSize().y;
						}
					}

					if (type == 0)
					{
						Objects::Block block(_windowSize.x - 100, posY, _windowSize);
						_renderBlocks.push_back(block);
						window.draw(block.getObject());
					}
					_objects.erase(obj);
				}
			}
			else _bgMusic.play();
		}
		else
		{
			if (_bgMusic.getStatus() == sf::SoundSource::Playing) 
				_bgMusic.pause();
		}

		window.draw(_floor);
	}
}