#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::Sprite _btn;
	sf::Texture _btnTex;

	std::string _imgPath;

	sf::Vector2f _btnScale;

	void setup();
public:
	Button();
	Button(std::string imgPath);
	~Button();

	bool isMouseOnBtn(sf::Vector2i mousePosition, sf::RenderWindow &window);

	void setPosition(sf::Vector2f pos);
	void setPosition(unsigned int x, unsigned int y);

	void resetScale();
	void setScale(float x);
	void setScale(float x, float y);
	void setScale(sf::Vector2f newScale);

	inline std::string getImagePath() { return _imgPath; }

	inline sf::Vector2f getScale() { return _btnScale; }
	inline sf::Sprite getSprite() { return _btn; }
	inline sf::Texture getTexture() { return _btnTex; }
};