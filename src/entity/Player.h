#pragma once

#include "../configs.h"

#include "../Level/objects/Block.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Game.h"

class Player
{
private:
	sf::Sprite _plr;
	sf::Texture _texture;
	sf::Vector2f _scale;

	std::string _texturePath;

	bool _isJumping = false;

	int _plrDefaultOffsetX = 50;
	int _plrDefaultOffsetY = 40;
	float _plrDefaultPosX = 0.0f;
	float _plrDefaultPosY = 0.0f;

	float _windowWidth = 0.0f;
	float _windowHeight = 0.0f;

	float _oldY = 0.0f;

	float _plrDefaultRotateSpeed = 8.0f;
	float _testVeloX = 0.0f;
	sf::Vector2f _velocity;

	float _jumpForce = -100.0f;

	void setup();
public:
	Player(std::string texturePath, float scale, sf::RenderWindow &window);
	Player(std::string texturePath, float scaleX, float scaleY, sf::RenderWindow &window);
	Player(std::string texturePath, sf::Vector2f scale, sf::RenderWindow &window);
	~Player();

	void reset();
	void update(sf::RenderWindow &window, int frames, Game &game);
	void draw(sf::RenderWindow &window);
	void jump();

	/*
	* 0 is for left
	* 1 is for right
	* 2 is for top
	* 3 is for bottom
	*/
	int collideWith(Objects::Block &block);

	void setPosition(float x, float y) { _plr.setPosition(sf::Vector2f(x, y)); };
	void setJumpForce(float jumpForce) { _jumpForce = jumpForce; }
	void setWindowWidth(float windowWidth) { _windowWidth = windowWidth; }
	void setWindowHeight(float windowHeight) { _windowHeight = windowHeight; }

	inline float getJumpForce() { return _jumpForce; }
	inline float getWindowWidth() { return _windowWidth; }
	inline float getWindowHeight() { return _windowHeight; }

	inline sf::Sprite getPlayer() { return _plr; }
	inline sf::Vector2f getScale() { return _scale; }
	inline std::string getTexturePath() { return _texturePath; }
};