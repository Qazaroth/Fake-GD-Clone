#pragma once

class Game
{
private:
	bool _isPaused = false;
	bool _isEnded = false;

	unsigned int _fpsCap = 0;
public:
	Game();
	~Game();

	void setPause(bool isPaused);
	void setEnded(bool isEnded);

	inline unsigned int getFPSCap() { return _fpsCap; }
	inline bool isPaused() { return _isPaused; }
	inline bool isEnded() { return _isEnded; }
};