#include "Image.h"

// Private:
void Image::setup()
{
	_imgScale.x = 1.125f;
	_imgScale.y = 1.125f;

	if (!_imgTexture.loadFromFile(_imgPath))
	{
		std::cout << "[ERROR] Error occured while loading background file!" << std::endl;;
		return;
	}

	_imgSprite.setTexture(_imgTexture);

	if (_isBG)
	{
		int min = 0;
		int max = 255;

		int r = min + (std::rand() % (max - min + 1));
		int g = min + (std::rand() % (max - min + 1));
		int b = min + (std::rand() % (max - min + 1));

		_imgSprite.setColor(sf::Color(r, g, b));
	}
	_imgSprite.setScale(_imgScale);
	_imgSprite.setOrigin((_imgTexture.getSize().x / 2), (_imgTexture.getSize().y / 2));
}

// Public
Image::Image(std::string imgPath, bool isBG) : _imgPath(imgPath), _isBG(isBG)
{
	setup();
}

Image::~Image()
{}

void Image::resetScale()
{
	_imgScale.x = 1.125f;
	_imgScale.y = 1.125f;
	_imgSprite.setScale(_imgScale);
}

void Image::setScale(float x)
{
	_imgScale = sf::Vector2f(x, x);
	_imgSprite.setScale(_imgScale);
}

void Image::setScale(float x, float y)
{
	_imgScale = sf::Vector2f(x, y);
	_imgSprite.setScale(_imgScale);
}

void Image::setScale(sf::Vector2f newScale)
{
	_imgScale = newScale;
	_imgSprite.setScale(_imgScale);
}

void Image::setPosition(float x, float y)
{
	sf::Vector2f pos(x, y);
	_imgSprite.setPosition(pos);
}

void Image::setPosition(sf::Vector2f pos)
{
	_imgSprite.setPosition(pos);
}

void Image::setColor(sf::Color color)
{
	_imgSprite.setColor(color);
}