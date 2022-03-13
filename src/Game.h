#pragma once

class Game
{
private:
	bool _isPaused = false;
	bool _isEnded = false;

	
public:
	Game();
	~Game();

	void setPause(bool isPaused);
	void setEnded(bool isEnded);

	
	inline bool isPaused() { return _isPaused; }
	inline bool isEnded() { return _isEnded; }
};