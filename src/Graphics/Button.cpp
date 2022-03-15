#include "Button.h"

// Private
void Button::setup()
{
	_btnScale = sf::Vector2f(1.125f, 1.125f);
	//_btnScale.x = 1.125f;
	//_btnScale.y = 1.125f;
	if (!_btnTex.loadFromFile(_imgPath))
	{
		std::cout << "[ERROR] Error occured while loading play texture file!" << std::endl;
		return;
	}

	_btn.setTexture(_btnTex);
	_btn.setScale(_btnScale);
	_btn.setOrigin((_btnTex.getSize().x / 2), (_btnTex.getSize().y / 2));
	_btn.setPosition(0, 0);
}
// Public
Button::Button() {}

Button::Button(std::string imgPath) : _imgPath(imgPath)
{
	setup();
}

Button::~Button() {}

bool Button::isMouseOnBtn(sf::Vector2i mousePosition, sf::RenderWindow &window)
{
	sf::FloatRect btnGlobalBounds = _btn.getGlobalBounds();

	int mouseX = mousePosition.x;
	int mouseY = mousePosition.y;

	float left = btnGlobalBounds.left;
	float top = btnGlobalBounds.top;
	float right = left + btnGlobalBounds.width;
	float bottom = top + btnGlobalBounds.height;

	if (left <= mouseX && mouseX <= right)
	{
		if (top <= mouseY && mouseY <= bottom)
		{
			return true;
		}
	}

	return false;
}

void Button::setPosition(sf::Vector2f pos)
{
	_btn.setPosition(pos);
}

void Button::setPosition(unsigned int x, unsigned int y)
{
	sf::Vector2f pos(x, y);

	_btn.setPosition(pos);
}

void Button::resetScale()
{
	_btnScale.x = 1.125f;
	_btnScale.y = 1.125f;
	_btn.setScale(_btnScale);
}

void Button::setScale(float x)
{
	_btnScale = sf::Vector2f(x, x);
	_btn.setScale(_btnScale);
}

void Button::setScale(float x, float y)
{
	_btnScale = sf::Vector2f(x, y);
	_btn.setScale(_btnScale);
}

void Button::setScale(sf::Vector2f newScale)
{
	_btnScale = newScale;
	_btn.setScale(newScale);
}
