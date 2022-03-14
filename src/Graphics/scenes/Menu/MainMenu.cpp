#include "MainMenu.h"

// Private
void MainMenu::setup()
{
	Button _p("res/img/play.png");
	playBtn = _p;
}
// Public
MainMenu::MainMenu() 
{
	setup();
}

MainMenu::~MainMenu() {}