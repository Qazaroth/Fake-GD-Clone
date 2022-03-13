#pragma once

#include <SFML/Graphics.hpp>

class Configs
{
private:
	float _floorHeight = 100.0f;
	float _floorWidth = 2560.0f;

	unsigned int _defaultWidth = 1920;
	unsigned int _defaultHeight = 1080;

	unsigned int _fpsCap = 60;

	sf::Vector2f _floorSize;
public:
	Configs();
	~Configs();

	inline unsigned int getFPSCap() { return _fpsCap; }

	inline sf::Vector2f getFloorSize() { return _floorSize; }
	inline sf::Vector2i getDefaultWindowSize() { return sf::Vector2i(_defaultWidth, _defaultHeight); }
};