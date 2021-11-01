#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "ManagerTexture.h"
#include "ManagerInput.h"
#include "SDL_Sprite.h"
#include "Cell.h"
#include "Gem.h"
#include "Bonus.h"
#include "Score.h"


class Game
{
public:
	Game();
	~Game();

	void Create(int, int);
	void Play();

private:

	void Update();
	void Render();

	bool GameLoop;

	int GS_width;
	int GS_height;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event	event;

	ManagerTexture managertexture;
	ManagerInput managerinput;

	void InitSDL();

	bool Chance(int chance);
	void Swap(std::shared_ptr<Cell> p1, std::shared_ptr<Cell> p2);
	void FindGemToMakeBonus(std::shared_ptr<Cell> p, std::pair<int, int>& p1);

	SDL_Sprite background, items, _score;
	int x0, y0, x, y;
	int click;
	SDL_Point pos;
	bool isSwap, isMoving, scoreWasCounted;
	bool recolorWasDropped, bombWasDropped;

	int ts;
	SDL_Point offset;

	Score score;
	std::shared_ptr <Cell> grid[10][10];
	std::vector<gemsToDoAction> arrOfGems; //arr of gems to do action on them after bonus's action 
};

