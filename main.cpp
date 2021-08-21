#include "Game.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main(int argc, char** argv) {
	Game game;
	game.Create(740, 480);
	game.Play();

	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	return 0;
}