#include "Block.h"

namespace Objects
{
	// Private
	void Block::setup()
	{
		_block.setSize(sf::Vector2f(_size, _size));
		_block.setPosition(_x, _y);

		if ((_block.getPosition().x > _windSize.x - _size) || (_block.getPosition().x < 0)) 
		{
			if ((_block.getPosition().y > _windSize.y - _size) || (_block.getPosition().y < 0))
			{
				_block.setPosition(_size, _size);
			}
			else
			{
				_block.setPosition(_size, _block.getPosition().y);
			}
		}

		_block.setFillColor(sf::Color::Black);
	}

	// Public
	Block::Block(float x, float y, sf::Vector2u windowSize)
	{
		_x = x;
		_y = y;
		_windSize = windowSize;

		setup();
	}

	Block::~Block() {}
}