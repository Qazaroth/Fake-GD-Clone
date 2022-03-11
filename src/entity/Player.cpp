#include "Player.h"

//Private
void Player::setup()
{
	if (!_texture.loadFromFile(_texturePath))
	{
		std::cout << "[ERROR] Error occured while loading player texture file!" << std::endl;
		return;
	}

	_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);

	_sprite.setTexture(_texture);
	_sprite.setColor(sf::Color::Green);
	_sprite.setScale(_scale);
}

//Public
Player::Player(std::string texturePath, float scale) : _texturePath(texturePath)
{
	sf::Vector2f scaleF(scale, scale);

	_scale = scaleF;
	
	setup();
}

Player::Player(std::string texturePath, float scaleX, float scaleY) : _texturePath(texturePath)
{
	sf::Vector2f scaleF(scaleX, scaleY);

	_scale = scaleF;
	
	setup();
}

Player::Player(std::string texturePath, sf::Vector2f scale) : _texturePath(texturePath), _scale(scale)
{
	setup();
}

Player::~Player() {}