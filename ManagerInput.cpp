#include "ManagerInput.h"

ManagerInput::ManagerInput() : _mouseCoords({ 0,0 }) { exit = false; }

void ManagerInput::Dispose(void) {
	_keyMap.clear();
	_previousKeyMap.clear();
}


ManagerInput::~ManagerInput() { Dispose(); }

void ManagerInput::update(SDL_Event event) {

	for (auto& it : _keyMap) {
		_previousKeyMap[it.first] = it.second;
	}

	wheel_x = false;
	wheel_y = false;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:				exit = true;								break;

		case SDL_KEYDOWN:			pressKey(event.key.keysym.sym);						break;
		case SDL_KEYUP:				releaseKey(event.key.keysym.sym);					break;

		case SDL_MOUSEMOTION:		setMouseCoords(event.motion.x, event.motion.y);		break;
		case SDL_MOUSEWHEEL:		wheelEvet(event.wheel.x, event.wheel.y);			break;

		case SDL_MOUSEBUTTONDOWN:	pressKey(event.button.button);						break;
		case SDL_MOUSEBUTTONUP:		releaseKey(event.button.button);					break;

		case SDL_WINDOWEVENT:

			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {}
			if (event.window.event == SDL_WINDOWEVENT_LEAVE) {}

			break;
		}
	}



}


void ManagerInput::pressKey(unsigned int keyID) {
	_keyMap[keyID] = true;
}

void ManagerInput::releaseKey(unsigned int keyID) {
	_keyMap[keyID] = false;
}

void ManagerInput::setMouseCoords(int x, int y) {
	_mouseCoords.x = x; _mouseCoords.y = y;
}

bool ManagerInput::isKeyDown(unsigned int keyID) {

	auto it = _keyMap.find(keyID);
	return it != _keyMap.end() ? it->second : false;
}

bool ManagerInput::isKeyPressed(unsigned int keyID) {
	if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) { return true; }
	return false;
}

bool ManagerInput::wasKeyDown(unsigned int keyID) {

	auto it = _previousKeyMap.find(keyID);
	return it != _previousKeyMap.end() ? it->second : false;
}
