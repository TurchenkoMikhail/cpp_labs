#pragma once

#include <SDL.h>
#include <unordered_map>

class ManagerInput {
public:
	ManagerInput();
	~ManagerInput();

	int wheel_x;
	int wheel_y;

	void update(SDL_Event event);

	void wheelEvet(int x, int y) {
		wheel_x = x;
		wheel_y = y;
	}


	void Dispose();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	void setMouseCoords(int x, int y);

	/// Returns true if the key is held down
	bool isKeyDown(unsigned int keyID);

	/// Returns true if the key was just pressed
	bool isKeyPressed(unsigned int keyID);

	//getters
	SDL_Point  getMouseCoords() const { return _mouseCoords; }

	bool exit;

private:
	/// Returns true if the key is held down
	bool wasKeyDown(unsigned int keyID);

	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _previousKeyMap;

	SDL_Point _mouseCoords;
};

