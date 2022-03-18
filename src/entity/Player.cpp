#include "Player.h"

//Private
void Player::setup()
{
	Configs configs;

	_velocity.x = _testVeloX;
	//_jumpForce = -50.0f;

	if (!_texture.loadFromFile(_texturePath))
	{
		std::cout << "[ERROR] Error occured while loading player texture file!" << std::endl;
		return;
	}

	_plr.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);

	_plr.setTexture(_texture);
	_plr.setColor(sf::Color::Green);
	_plr.setScale(_scale);

	_plrDefaultPosX = _plrDefaultOffsetX + ((_texture.getSize().x * _scale.x) / 2);
	_plrDefaultPosY = (_windowHeight - configs.getFloorSize().y) - (_texture.getSize().y * _scale.y) + _plrDefaultOffsetY;
	sf::Vector2f plrDefaultPos(_plrDefaultPosX, _plrDefaultPosY);
	_oldY = plrDefaultPos.y;

	_plr.setPosition(plrDefaultPos);
}

//Public
Player::Player(std::string texturePath, float scale, sf::RenderWindow &window) : _texturePath(texturePath)
{
	sf::Vector2f scaleF(scale, scale);

	_scale = scaleF;
	_windowWidth = window.getSize().x;
	_windowHeight = window.getSize().y;
	
	setup();
}

Player::Player(std::string texturePath, float scaleX, float scaleY, sf::RenderWindow &window) : _texturePath(texturePath)
{
	sf::Vector2f scaleF(scaleX, scaleY);

	_scale = scaleF;
	_windowWidth = window.getSize().x;
	_windowHeight = window.getSize().y;
	
	setup();
}

Player::Player(std::string texturePath, sf::Vector2f scale, sf::RenderWindow &window) : _texturePath(texturePath), _scale(scale)
{
	_windowWidth = window.getSize().x;
	_windowHeight = window.getSize().y;
	setup();
}

Player::~Player() {}

void Player::update(sf::RenderWindow &window, int frames, Game &game)
{
	Configs config;

	bool isPaused = game.isPaused();

	if (game.getGameState() == GameState::IN_LEVEL)
	{
		//float maxY = windHeight - (plrTexture.getSize().y * plr.getScale().y / (10 / plr.getScale().y));
		float defaultWindowHeight = config.getDefaultWindowSize().y;
		float defaultWindowWidth = config.getDefaultWindowSize().x;

		sf::Vector2u windowSize = window.getSize();
		float windowHeight = windowSize.y;
		float windowWidth = windowSize.x;

		float maxY = (defaultWindowHeight - ((30 / defaultWindowHeight) * windowHeight)) - ((_texture.getSize().y * _scale.y) / 2);
		float maxX = (defaultWindowWidth - ((15 / defaultWindowWidth) * windowWidth)) - ((_texture.getSize().x * _scale.x) / 2);
		float minX = (_texture.getSize().x * _plr.getScale().x) - 30;
		float minY = (_texture.getSize().y * _plr.getScale().y) - 30;

		if (!isPaused)
		{
			_plr.move(_velocity);
		}

		if (_plr.getPosition().y < minY)
		{
			_plr.setPosition(_plr.getPosition().x, minY);
		}
		else if (_plr.getPosition().y > maxY)
		{
			_plr.setPosition(_plr.getPosition().x, maxY);
		}

		if (_plr.getPosition().x < minX)
		{
			_velocity.x = _testVeloX;//(5.0f/defaultWidth) * windWidth;
		}
		else if (_plr.getPosition().x > maxX)
		{
			_velocity.x = -_testVeloX;//((5.0f / defaultWidth) * windWidth);
		}

		if ((_plr.getPosition().y < _oldY) && !isPaused)
		{
			float gravity = (1.25f * (1.25) * (125 / 50)) * 0.5;

			_plr.move(0.0f, gravity);
			//_plr.rotate(_plrDefaultRotateSpeed);
		}

		if (!_isJumping || _plr.getPosition().y == _oldY)
		{
			_isJumping = false;
			_plr.setRotation(0.0f);
		}

		if (_plr.getPosition().y >= _windowHeight)
		{
			_plr.setPosition(_plr.getPosition().x, _plrDefaultPosY);
		}
	}
	else
	{
		_isJumping = false;
		_plr.setPosition(_plrDefaultPosX, _plrDefaultPosY);
	}
}

void Player::reset()
{
	_plr.setPosition(_plrDefaultPosX, _plrDefaultPosY);
}

void Player::draw(sf::RenderWindow &window)
{
	window.draw(_plr);
}

void Player::jump()
{
	if (!_isJumping)
	{
		_plr.move(sf::Vector2f(0.0f, _jumpForce * 1.5));
		_isJumping = true;
	}
}

int Player::collideWith(Objects::Block &block)
{
	sf::FloatRect plrGlobalBounds = _plr.getGlobalBounds();
	sf::FloatRect blockGlobalBounds = block.getObject().getGlobalBounds();

	if (plrGlobalBounds.intersects(blockGlobalBounds))
	{
		float blockY = block.getObject().getPosition().y - (block.getSize() * 0.9);
		float heightDiff = blockY - (_plr.getPosition().y);

		std::cout << "Height diff: " << heightDiff << std::endl;

		_oldY = _plr.getPosition().y;
		_isJumping = false;

		bool isValidHeightDiff = heightDiff <= -27.5f && heightDiff >= -32.0f;

		if (isValidHeightDiff) return 2;
		else return 1;
	}

	_oldY = _plrDefaultPosY;
	return 0;
}