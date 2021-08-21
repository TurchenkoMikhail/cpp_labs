#pragma once
//#include <iostream>
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



<<<<<<< Updated upstream
	void create(int, int);
	void play();
=======
	void Create(int, int);
	void Play();
>>>>>>> Stashed changes

private:

	void update();
	void render();


	bool GameLoop;

	int GS_width;
<<<<<<< Updated upstream
	int GS_height;  // размеры окна
=======
	int GS_height; 
>>>>>>> Stashed changes

	SDL_Window			*window;   // ссылка на окно
	SDL_Renderer		*renderer; // ссылка на рендер
	SDL_Event			 event;     // события нажатия клавиш

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
<<<<<<< Updated upstream
	//SDL_Sprite* secondPaddle;
=======
>>>>>>> Stashed changes
	
	int paddleSize;

	bool secondPaddleWasCreated;
	bool isPaddleResized;
	bool isMagnetActivated;
	bool isBlockDamaged; //for healthy blocks

	Ball sBall[2];

	//numbers of blocks
	int n = 0;
};

