#include "Window.h"

namespace Graphics
{
	//Private
	void Window::init()
	{
		_window.create(sf::VideoMode(_width, _height), _title);
	}
	//Public
	Window::Window(std::string title)
		: _width(_defaultWidth), _height(_defaultHeight), _title(title)
	{
		init();
	}

	Window::Window(unsigned int width, unsigned int height, std::string title)
		: _width(width), _height(height), _title(title)
	{
		init();
	}

	Window::~Window() {}
}