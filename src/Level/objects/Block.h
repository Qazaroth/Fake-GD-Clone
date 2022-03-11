#pragma once

#include <SFML/Graphics.hpp>

namespace Objects
{
	class Block
	{
	private:
		float _x, _y;
		float _size = 10.0f;

		sf::RectangleShape _block;
		sf::Vector2u _windSize;

		void setup();
	public:
		Block(float x, float y, sf::Vector2u windowSize);
		~Block();

		inline sf::RectangleShape getObject() { return _block; }

		inline sf::Vector2f getPosition() { return sf::Vector2f(_x, _y); }
	};
}