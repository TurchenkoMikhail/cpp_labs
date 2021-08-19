#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "ManagerTexture.h"
#include "ManagerInput.h"
#include "SDL_Sprite.h"
#include "Block.h"
#include "Ball.h"
#include "Bonus.h"
#include <cmath>


class Game {
public:
	Game();
	~Game();



	void create(int, int);
	void play();

private:

	void update();
	void render();


	bool GameLoop;

	int GS_width;
	int GS_height;  // размеры окна

	SDL_Window			*window;   // ссылка на окно
	SDL_Renderer		*renderer; // ссылка на рендер
	SDL_Event			 event;     // события нажатия клавиш

	ManagerTexture managertexture;
	ManagerInput managerinput;

	void InitSDL();

	// данные игры

	std::shared_ptr<Block> block[100];
	std::shared_ptr<Bonus> bonuses[100];
	int bonusSize;

	int FindBonusInVector(int i, int j);

	SDL_Sprite sBackground, sPaddle;
	SDL_Sprite* secondPaddle;
	int paddleSize;

	bool secondPaddleWasCreated;
	bool isPaddleResized;
	bool isMagnetActivated;
	bool isBlockDamaged; //for healthy blocks

	Ball sBall;

	//numbers of blocks
	int n = 0;
};

