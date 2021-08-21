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

	int score;

	std::shared_ptr<Block> block[100];
	std::shared_ptr<Bonus> bonuses[100];
	int bonusSize;

	int FindBonusInVector(int i, int j);
	bool CheckWin();

	SDL_Sprite sBackground, sPaddle, secondPaddle;
	bool secondPaddleIsActive;
	
	int paddleSize;

	bool secondPaddleWasCreated;
	bool isPaddleResized;
	bool isMagnetActivated;
	bool isBlockDamaged; //for healthy blocks

	Ball sBall[2];

	//numbers of blocks
	int n = 0;
};

