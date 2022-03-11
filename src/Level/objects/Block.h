#pragma once

#include <SFML/Graphics.hpp>

namespace Objects
{
	class Block
	{
	private:
		float _x, _y;

		sf::RectangleShape _block;

		void setup();
	public:
		Block(float x, float y);
		~Block();

		inline sf::Vector2f getPosition() { return sf::Vector2f(_x, _y); }
	};
}