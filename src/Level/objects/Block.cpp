#include "Block.h"

namespace Objects
{
	// Private
	void Block::setup()
	{
		_block.setSize(sf::Vector2f(10.0f, 10.0f));
		_block.setPosition(_x, _y);
		_block.setFillColor(sf::Color::Black);
	}

	// Public
	Block::Block(float x, float y)
	{
		_x = x;
		_y = y;

		setup();
	}

	Block::~Block() {}
}