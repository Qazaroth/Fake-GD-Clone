#pragma once

class Game
{
private:
	bool _isPaused = false;
	bool _isEnded = false;
	bool _showFPSCounter = false;
public:
	Game();
	~Game();

	void setPause(bool isPaused);
	void setEnded(bool isEnded);
	void toggleFPSCounter();

	inline bool showFPS() { return _showFPSCounter; }
	inline bool isPaused() { return _isPaused; }
	inline bool isEnded() { return _isEnded; }
};