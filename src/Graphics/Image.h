#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "../utils/Random.h"

class Image
{
private:
	sf::Sprite _imgSprite;
	sf::Texture _imgTexture;

	sf::Vector2f _imgScale;

	std::string _imgPath;

	bool _isBG = false;

	void setup();
public:
	Image();
	Image(std::string imgPath, bool isBG=false, bool preload=true);
	~Image();

	void loadImage();

	void resetScale();
	void setScale(float x);
	void setScale(float x, float y);
	void setScale(sf::Vector2f newScale);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f pos);
	void setColor(sf::Color color);

	inline std::string getImagePath() { return _imgPath; }

	inline sf::Vector2f getPosition() { return _imgSprite.getPosition(); }
	inline sf::Vector2f getScale() { return _imgScale; }
	inline sf::Sprite getSprite() { return _imgSprite; }
	inline sf::Texture getTexture() { return _imgTexture; }
};
