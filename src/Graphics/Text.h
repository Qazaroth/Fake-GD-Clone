#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Text
{
private:
	sf::Font _font;
	sf::Text _text;

	std::string _fontPath;

	std::string _defaultText = "";

	void setup();
public:
	Text(std::string fontPath);
	Text(std::string fontPath, std::string defaultText);
	~Text();

	void setText(std::string newText);
	void setCharacterSize(int charSize);
	void setFillColor(sf::Color color);

	inline sf::Font getFont() { return _font; }
	inline sf::Text getSFText() { return _text; }

	inline std::string getDefaultText() { return _defaultText; }

	inline int getCharacterSize() { return _text.getCharacterSize(); }
};