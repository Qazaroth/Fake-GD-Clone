#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace Objects
{
	class Block : public sf::Drawable
	{
	private:
		float _x, _y;
		float _size = 75.0f;

		sf::RectangleShape _block;
		sf::Vector2u _windSize;

		void setup();
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
		{
			target.draw(_block, states);
		}
	public:
		Block(float x, float y, sf::Vector2u windowSize);
		~Block();

		inline sf::RectangleShape getObject() { return _block; }

		inline sf::Vector2f getPosition() { return sf::Vector2f(_x, _y); }
	};
}