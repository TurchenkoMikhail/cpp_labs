#include "Game.h"
#include <time.h>

Game::Game() {
	GameLoop = true;
	GS_width = 1024;
	GS_height = 768;
}

Game::~Game() {
	managertexture.Dispose();
	managerinput.Dispose();

	if (renderer)
		SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	if (window)
		SDL_DestroyWindow(window);
	window = 0;

	SDL_Quit();
}



void Game::create(int w, int h) {

	srand((unsigned)time(NULL));

	GS_width = w;
	GS_height = h;
	GameLoop = true;

	InitSDL();

	managertexture.SetRender(renderer);

	sBackground.setTexture(managertexture.getTexture("background.jpg"));
	sBall.setTexture(managertexture.getTexture("ball.png"));
	sPaddle.setTexture(managertexture.getTexture("paddle_size1.png"));

	sPaddle.setPosition(300, 440);
	
	isPaddleResized = false;
	bonusSize = 0;
	paddleSize = 1;

	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {

			int kind = rand() % 5;
			//int kind = 2;

			if (kind == 0) {
				UsualBlock* blockptr = new UsualBlock;
				std::shared_ptr <UsualBlock> ptr(blockptr);
				block[n] = ptr;
				block[n]->setTexture(managertexture.getTexture("block01.png"));
			}
			else if (kind == 1) {
				NonDestroyableBlock* blockptr = new NonDestroyableBlock;
				std::shared_ptr <NonDestroyableBlock> ptr(blockptr);
				block[n] = ptr;
				block[n]->setTexture(managertexture.getTexture("block02.png"));
			}
			else if (kind == 2) {
				BonusBlock* blockptr = new BonusBlock;
				blockptr->arr = &bonuses;
				blockptr->bonusSize = &bonusSize;
				std::shared_ptr <BonusBlock> ptr(blockptr);
				block[n] = ptr;
				block[n]->setTexture(managertexture.getTexture("block03.png"));

				//put one bonus to block
				int bonus_kind = rand() % 8;

				if (bonus_kind == 0) {
					BonusBiggerCarriageSize* bonus = new BonusBiggerCarriageSize;
					std::shared_ptr <BonusBiggerCarriageSize> ptr(bonus);
					ptr->isPaddleResized = &isPaddleResized;
					ptr->paddleSize = &paddleSize;
					ptr->setTexture(managertexture.getTexture("bonus_bigger_paddle.png"));
					bonuses[bonusSize] = ptr;
				}
				if (bonus_kind == 1) {
					BonusSmallerCarriageSize* bonus = new BonusSmallerCarriageSize;
					std::shared_ptr <BonusSmallerCarriageSize> ptr(bonus);
					ptr->isPaddleResized = &isPaddleResized;
					ptr->paddleSize = &paddleSize;
					ptr->setTexture(managertexture.getTexture("bonus_smaller_paddle.png"));
					bonuses[bonusSize] = ptr;
				}

				else if (bonus_kind == 2) {
					BoostSpeed* bonus = new BoostSpeed;
					std::shared_ptr <BoostSpeed> ptr(bonus);
					ptr->ball = &sBall;
					ptr->setTexture(managertexture.getTexture("bonus_bigger_speed.png"));
					bonuses[bonusSize] = ptr;
				}

				else if (bonus_kind == 3) {
					DecreaseSpeed* bonus = new DecreaseSpeed;
					std::shared_ptr <DecreaseSpeed> ptr(bonus);
					ptr->ball = &sBall;
					ptr->setTexture(managertexture.getTexture("bonus_smaller_speed.png"));
					bonuses[bonusSize] = ptr;
				}

				else if (bonus_kind == 4) {
					Magnet* bonus = new Magnet;
					std::shared_ptr <Magnet> ptr(bonus);
					ptr->setTexture(managertexture.getTexture("bonus_magnet.png"));
					bonuses[bonusSize] = ptr;
				}
				else if (bonus_kind == 5) {
					SecondCarriage* bonus = new SecondCarriage;
					std::shared_ptr <SecondCarriage> ptr(bonus);
					ptr->setTexture(managertexture.getTexture("bonus_new_carriage.png"));
					bonuses[bonusSize] = ptr;
				}
				else if (bonus_kind == 6) {
					ChangePathBall* bonus = new ChangePathBall;
					std::shared_ptr <ChangePathBall> ptr(bonus);
					ptr->setTexture(managertexture.getTexture("bonus_new_way.png"));
					bonuses[bonusSize] = ptr;
				}
				else if (bonus_kind == 7) {
					SecondBall* bonus = new SecondBall;
					std::shared_ptr <SecondBall> ptr(bonus);
					ptr->setTexture(managertexture.getTexture("bonus_new_ball.png"));
					bonuses[bonusSize] = ptr;
				}
				bonuses[bonusSize]->x = i;
				bonuses[bonusSize]->y = j;
				++bonusSize;
				//adding bonuses

			}//if block drops bonus

			else if (kind == 3) {
				ChangeSpeedBlock* blockptr = new ChangeSpeedBlock;
				std::shared_ptr <ChangeSpeedBlock> ptr(blockptr);
				ptr->ball = &sBall;
				block[n] = ptr;
				block[n]->setTexture(managertexture.getTexture("block04.png"));
			}
			else if (kind == 4) {
				HealthyBlock* blockptr = new HealthyBlock;
				std::shared_ptr <HealthyBlock> ptr(blockptr);
				block[n] = ptr;
				block[n]->setTexture(managertexture.getTexture("block05.png"));
			}

			block[n]->setPosition(i * 43, j * 20);
			block[n]->x = i;
			block[n]->y = j;
			n++;
		}
	}
	sBall.dx = 5;
	sBall.dy = 4;
	sBall.x = 300;
	sBall.y = 300;
}



void Game::InitSDL() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());

	Uint32 flagsW = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

	window = SDL_CreateWindow("Arkanoid!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GS_width, GS_height, flagsW);
  if (!window)
		printf("SDL window not create! SDL Error: %s\n", SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		printf("SDL render not create! SDL Error: %s\n", SDL_GetError());
}


void Game::play() {

	while (GameLoop) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // цвет обнуления экрана черный
		SDL_RenderClear(renderer);
		update();
	  render();
	}
}

void Game::update() {

	managerinput.update(event);

	if (managerinput.exit)
		GameLoop = false;

	sBall.x += sBall.dx;
	//ball strikes block from the side
	for (int i = 0; i < n; i++) {
		SDL_Rect a = { sBall.x + 3, sBall.y + 3, 6, 6 };
		SDL_FRect b = block[i]->getRect();
		SDL_Rect c = { b.x,b.y,b.w,b.h };
		if (SDL_HasIntersection(&a, &c)) {
			block[i]->DoAction();

			// check is bonus was dropped
			for (int j = 0; j < bonusSize; ++j) {
				//set falling of bonus
				if (bonuses[j]->isDropped == true) {
					bonuses[j]->isDropped = false;
					bonuses[j]->isFalling = true;
					bonuses[j]->x *= 43; //coords in pixels
					bonuses[j]->y *= 20;
					bonuses[j]->setPosition(bonuses[j]->x, bonuses[j]->y);
					break;
				}
			}
			sBall.dx = -sBall.dx;
		}
	}

	sBall.y += sBall.dy;
	//ball strikes block from up/down
	for (int i = 0; i < n; i++) {
		SDL_Rect a = { sBall.x + 3, sBall.y + 3, 6, 6 };
		SDL_FRect b = block[i]->getRect();
		SDL_Rect c = { b.x,b.y,b.w,b.h };
		if (SDL_HasIntersection(&a, &c)) {
			block[i]->DoAction();

			//check is bonus was dropped
			for (int j = 0; j < bonusSize; ++j) {

				//set falling of bonus
				if (bonuses[j]->isDropped == true) {
					bonuses[j]->isDropped = false;
					bonuses[j]->isFalling = true;
					bonuses[j]->x *= 43; //coords in pixels
					bonuses[j]->y *= 20;
					bonuses[j]->setPosition(bonuses[j]->x, bonuses[j]->y);
					break;
				}

			}

			sBall.dy = -sBall.dy;
		}
	}

	//check if ball went out from screen
	if (sBall.x < 0 || sBall.x>520)
		sBall.dx = -sBall.dx;
	if (sBall.y < 0 || sBall.y>450)
		sBall.dy = -sBall.dy;

	if (managerinput.isKeyDown(SDLK_RIGHT))
		sPaddle.move(6, 0);
	if (managerinput.isKeyDown(SDLK_LEFT))
		sPaddle.move(-6, 0);

	//intersection ball and bonuses with paddle
	SDL_Rect a = { sBall.x, sBall.y, 12, 12 };
	SDL_FRect b = sPaddle.getRect();
	SDL_Rect c = { b.x,b.y,b.w,b.h };
	if (SDL_HasIntersection(&a, &c))
		sBall.dy = -(rand() % 5 + 2);

	for (int i = 0; i < bonusSize; ++i) {
		if (bonuses[i]->isFalling == true) {

			SDL_Rect bonus = { bonuses[i]->x, bonuses[i]->y, 42, 42 };
			if (SDL_HasIntersection(&bonus, &c)) {
				bonuses[i]->isFalling = false;
				bonuses[i]->setPosition(-100, 0);

				//activating bonus
				bonuses[i]->IsActivated();

				if(isPaddleResized == true) {
					isPaddleResized = false;

					SDL_FPoint paddlePos = sPaddle.getPosition();
					if(paddleSize==1)
						sPaddle.setTexture(managertexture.getTexture("paddle_size1.png"));
					else if(paddleSize == 2)
					  sPaddle.setTexture(managertexture.getTexture("paddle_size2.png"));
					else if(paddleSize == 3)
						sPaddle.setTexture(managertexture.getTexture("paddle_size3.png"));
					else if (paddleSize == 4)
						sPaddle.setTexture(managertexture.getTexture("paddle_size4.png"));
					else if (paddleSize == 5)
						sPaddle.setTexture(managertexture.getTexture("paddle_size5.png"));

					//y = 440
					sPaddle.setPosition(paddlePos.x, paddlePos.y);
				}


			}

		}
	}

	sBall.setPosition(sBall.x, sBall.y);

	//bonus falling animation
	for (int i = 0; i < bonusSize; ++i) {
		if (bonuses[i]->isFalling == true) {
			bonuses[i]->y += bonuses[i]->dy;
			bonuses[i]->setPosition(bonuses[i]->x, bonuses[i]->y);
		}
	}
	
}

void Game::render() {

	sBackground.draw(renderer);
	sBall.draw(renderer);
	sPaddle.draw(renderer);

	for (int i = 0; i < bonusSize; ++i) {
		if(bonuses[i]->isFalling == true)
		   bonuses[i]->draw(renderer);
	}
	for (int i = 0; i < n; i++)
		block[i]->draw(renderer);
	
	SDL_RenderPresent(renderer);
}

int Game::FindBonusInVector(int i, int j) {
	for (int k = 0; i < bonusSize; ++k) {
		if (bonuses[k]->x == i && bonuses[k]->y == j)
			return k;
	}
	return -1;
}