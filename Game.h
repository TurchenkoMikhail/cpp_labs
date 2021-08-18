#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "ManagerTexture.h"
#include "ManagerInput.h"
#include "SDL_Sprite.h"
#include "Block.h"
#include "Ball.h"
#include "Bonus.h"


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
	int GS_height;  // ������� ����

	SDL_Window			*window;   // ������ �� ����
	SDL_Renderer		*renderer; // ������ �� ������
	SDL_Event			 event;     // ������� ������� ������

	ManagerTexture managertexture;
	ManagerInput managerinput;

	void InitSDL();

	// ������ ����

	std::shared_ptr<Block> block[100];
	//std::vector <Bonus> bonuses;
	std::shared_ptr<Bonus> bonuses[100];
	int bonusSize;

	int FindBonusInVector(int i, int j);

	SDL_Sprite sBackground, sPaddle;
	int paddleSize;
	bool isPaddleResized;

	Ball sBall;

	//numbers of blocks
	int n = 0;
};

