#pragma once

#include "Graphics/scenes/Menu/MainMenu.h"
#include <SFML/Graphics.hpp>

enum class GameState
{
	IN_MAINMENU,
	IN_LEVEL
};

class Game
{
private:
	bool _isPaused = false;
	bool _isEnded = false;
	bool _showFPSCounter = false;

	GameState _state;
public:
	Game();
	~Game();

	void setPause(bool isPaused);
	void setEnded(bool isEnded);
	void toggleFPSCounter();

	void setGameState(GameState state);

	inline GameState getGameState() { return _state; }

	inline bool showFPS() { return _showFPSCounter; }
	inline bool isPaused() { return _isPaused; }
	inline bool isEnded() { return _isEnded; }
};