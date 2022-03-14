#include "Text.h"

// Private:
void Text::setup()
{
	if (!_font.loadFromFile(_fontPath))
	{
		std::cout << "[ERROR] Error occured while loading font file!" << std::endl;
		return;
	}

	_text.setFont(_font);
	_text.setCharacterSize(24);
	_text.setString(_defaultText);
}
// Public:
Text::Text(std::string fontPath) : _fontPath(fontPath)
{
	setup();
}

Text::Text(std::string fontPath, std::string defaultText) : _fontPath(fontPath), _defaultText(defaultText)
{
	setup();
}

Text::~Text() {}

void Text::setText(std::string newText)
{
	_text.setString(newText);
}

void Text::setCharacterSize(int charSize)
{
	_text.setCharacterSize(charSize);
}

void Text::setFillColor(sf::Color color)
{
	_text.setFillColor(color);
}