#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _scale;

	std::string _texturePath;

	void setup();
public:
	Player(std::string texturePath, float scale);
	Player(std::string texturePath, float scaleX, float scaleY);
	Player(std::string texturePath, sf::Vector2f scale);
	~Player();

	inline sf::Vector2f getScale() { return _scale; }
	inline std::string getTexturePath() { return _texturePath; }
};