#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace Objects
{
	class Block
	{
	private:
		float _x, _y;
		float _size = 75.0f;

		sf::RectangleShape _block;
		sf::Vector2u _windSize;

		void setup();
	public:
		Block(float x, float y, sf::Vector2u windowSize);
		~Block();

		void move(sf::Vector2f velocity);

		inline float getSize() { return _size; }

		inline sf::RectangleShape getObject() { return _block; }
		inline sf::Vector2f getPosition() { return sf::Vector2f(_x, _y); }

		bool operator== (Block const &other);
	};
}