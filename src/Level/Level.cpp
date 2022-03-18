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
		float posT = val["pos_T"];
		std::string posYStr;
		int posY = 0;
		bool isYRelative = false;
		
		try
		{ 
			posYStr = val["pos_Y"];
			std::transform(posYStr.begin(), posYStr.end(), posYStr.begin(), [](unsigned char c) { return std::tolower(c); });
			
			if (posYStr == "height")
			{
				posY = _windowSize.y - config.getFloorSize().y - 75.0f;
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

void Level::randomize()
{
	Configs config;
	srand(time(NULL));

	_renderBlocks.clear();
	if (_objects.size() > 0)
	{
		std::map<int, std::list<std::string>> _newObjects;

		unsigned int pnSeed = 0 + (std::rand() % (999999 - 0 + 1));

		std::cout << pnSeed << std::endl;

		for (auto i = _objects.begin(); i != _objects.end(); i++)
		{
			int type = std::stoi(getDataOfObject(i->second, 0));
			int posT = std::stoi(getDataOfObject(i->second, 1));
			std::string posYStr = getDataOfObject(i->second, 2);
			auto posY = std::stoi(getDataOfObject(i->second, 3));
			std::string isYRelativeStr = getDataOfObject(i->second, 4);
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
			int min = 0;
			int max = _windowSize.y - config.getFloorSize().y;
			int y = min + (std::rand() % (max - min + 1));
			std::cout << y << std::endl;
			//PerlinNoise pn; // (pnSeed);
			//double k = pn.noise(posT, posY, 1);
			//std::cout << k << std::endl;
		}

		_objects = _newObjects;
	}
	//resetLevel();

	
}

void Level::move(sf::Vector2f velocity, Game game)
{
	if (_renderBlocks.size() > 0 && !(game.isPaused()))
	{
		std::list<Objects::Block> _newRenderBlocks;

		for (auto i = _renderBlocks.begin(); i != _renderBlocks.end(); i++) 
		{
			Objects::Block b = (*i);

			float limit = 0 - (b.getSize() / 1);

			if (b.getObject().getPosition().x > limit)
			{
				b.move(sf::Vector2f(defaultLevelSpeed * levelSpeed, 0.0f));
				_newRenderBlocks.push_back(b);
			}
		}
		_renderBlocks = _newRenderBlocks;
	}
}

void Level::reloadData()
{
	Configs config;

	_lvlJson = nlohmann::json::parse(_lvlData);
	_objsArr = _lvlJson["objects"];

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
				posY = _windowSize.y - config.getFloorSize().y - 75.0f;
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
}

void Level::resetLevel()
{
	stopBGMusic();
	_objects.clear();
	_renderBlocks.clear();
	_lvlTimer = 0;
}

void Level::stopBGMusic()
{
	_bgMusic.stop();
}

void Level::update(sf::RenderWindow &window, Player &plr, Game &game)
{
	Configs config;

	if (_objects.empty())
		reloadData();

	sf::FloatRect plrGlobalBounds = plr.getPlayer().getGlobalBounds();

	bool isMusicPlaying = _bgMusic.getStatus() == sf::SoundSource::Playing;

	if (game.getGameState() != GameState::IN_LEVEL)
	{
		_lvlTimer = 0;
		_renderBlocks.clear();
		window.clear();
		return;
	}

	if (_IsInit)
	{
		move(sf::Vector2f(-5.0f, 0.0f), game);

		window.draw(_background);

		_windowSize = window.getSize();
		_lvlTimer = _bgMusic.getPlayingOffset().asSeconds();

		if (_renderBlocks.size() > 0)
		{
			for (int i = 0; i < _renderBlocks.size(); i++)
			{
				std::list<Objects::Block>::iterator e = _renderBlocks.begin();
				std::advance(e, i);

				Objects::Block b = (*e);

				window.draw(b.getObject());
				int plrCollision = plr.collideWith(b);
				if (plrCollision > 0) std::cout << plrCollision << std::endl;
				if (plrCollision == 2)
				{
					float newPlrX = plr.getPlayer().getPosition().x;
					float newPlrY = b.getPosition().y - b.getSize() / 2;
					plr.setPosition(newPlrX, newPlrY);
				}
				else if (plrCollision == 1)
				{
					std::cout << "Player died!" << std::endl;
					game.setEnded(true);
				}
			}
		}

		if (!game.isPaused())
		{
			if (isMusicPlaying)
			{
				if (_objects.count(_lvlTimer))
				{
					auto obj = _objects.find(_lvlTimer);

					int type = std::stoi(getDataOfObject(obj->second, 0));
					float posT = std::stof(getDataOfObject(obj->second, 1));
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
							posY = _windowSize.y - config.getFloorSize().y - 75.0f;
						}
					}

					if (type == 0)
					{
						Objects::Block block(_windowSize.x - 75.0f, posY, _windowSize);
						_renderBlocks.push_back(block);
						window.draw(block.getObject());
					}
					_objects.erase(obj);
				}
				/*
				for (auto o = _objects.begin(); o != _objects.end(); o++)
				{
					auto obj = (*o);

					int type = std::stoi(getDataOfObject(o->second, 0));
					int posT = std::stoi(getDataOfObject(o->second, 1));
					std::string posYStr = getDataOfObject(o->second, 2);
					auto posY = std::stoi(getDataOfObject(o->second, 3));
					std::string isYRelativeStr = getDataOfObject(o->second, 4);
					bool isYRelative;

					//if (_bgMusic.)
				}
				*/
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