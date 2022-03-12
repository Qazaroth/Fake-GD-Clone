#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Graphics
{
	class Window
	{
	private:
		unsigned int _width, _height;
		unsigned int _defaultWidth = 1080;
		unsigned int _defaultHeight = 1920;

		std::string _title;

		void init();
	public:
		sf::RenderWindow _window;

		Window(std::string title);
		Window(unsigned int width, unsigned int height, std::string title);
		~Window();

		inline std::string getTitle() const { return _title; }

		inline bool isOpen() const { return _window.isOpen(); }

		inline sf::Vector2u getSize() const { return _window.getSize(); }

		void display() { _window.display(); }

		inline int getWidth() const { return _width; }
		inline int getDefaultWidth() const { return _defaultWidth; }
		inline int getHeight() const { return _height; }
		inline int getDefaultHeight() const { return _defaultHeight; }
	};
}