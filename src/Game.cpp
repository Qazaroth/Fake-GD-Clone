#include "Game.h"

// Private

// Public
Game::Game() 
{
}
Game::~Game() {}

void Game::setPause(bool isPaused)
{
	_isPaused = isPaused;
}

void Game::setEnded(bool isEnded)
{
	_isEnded = isEnded;
}

void Game::toggleFPSCounter()
{
	_showFPSCounter = !_showFPSCounter;
}

void Game::setGameState(GameState state)
{
	_state = state;
}