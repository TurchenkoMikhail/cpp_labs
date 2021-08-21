#include "Game.h"
#include <time.h>

Game::Game() {
	GameLoop = true;
	GS_width = 1024;
	GS_height = 768;
}

Game::~Game() {
	std::cout << "Your score : " << score <<"\n";

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



void Game::Create(int w, int h) {

	srand((unsigned)time(NULL));

	GS_width = w;
	GS_height = h;
	GameLoop = true;

	InitSDL();

	managertexture.SetRender(renderer);

	sBackground.setTexture(managertexture.getTexture("background.jpg"));
	sBall[0].setTexture(managertexture.getTexture("ball.png"));
	sBall[1].setTexture(managertexture.getTexture("ball.png"));
	sPaddle.setTexture(managertexture.getTexture("paddle_size1.png"));

	sPaddle.setPosition(300, 440);
	
	isPaddleResized = false;
	bonusSize = 0;
	paddleSize = 1;
	isMagnetActivated = false;
	secondPaddleIsActive = false;
	secondPaddleWasCreated = false;

	score = 0;

	sBall[0].isActive = true;
	sBall[1].isActive = false;

	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {

			int kind = rand() % 5;

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
					ptr->isMagnetActivated = &isMagnetActivated;
					ptr->setTexture(managertexture.getTexture("bonus_magnet.png"));
					bonuses[bonusSize] = ptr;
				}
				else if (bonus_kind == 5) {
					SecondCarriage* bonus = new SecondCarriage;
					std::shared_ptr <SecondCarriage> ptr(bonus);
					ptr->secondPaddleIsActive = &secondPaddleIsActive;
					ptr->secondPaddleWasCreated = &secondPaddleWasCreated;
					ptr->setTexture(managertexture.getTexture("bonus_new_carriage.png"));
					bonuses[bonusSize] = ptr;
				}
				else if (bonus_kind == 6) {
					ChangePathBall* bonus = new ChangePathBall;
					std::shared_ptr <ChangePathBall> ptr(bonus);
					ptr->ball = &sBall;
					ptr->setTexture(managertexture.getTexture("bonus_new_way.png"));
					bonuses[bonusSize] = ptr;
				}
				else if (bonus_kind == 7) {
					SecondBall* bonus = new SecondBall;
					std::shared_ptr <SecondBall> ptr(bonus);
					ptr->ball = &sBall;
					ptr->setTexture(managertexture.getTexture("bonus_new_ball.png"));
					bonuses[bonusSize] = ptr;
				}
				bonuses[bonusSize]->score = &score;
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
				ptr->isBlockDamaged = &isBlockDamaged;
				block[n] = ptr;
				block[n]->setTexture(managertexture.getTexture("block05_life3.png"));
			}
			block[n]->kind = kind;
			block[n]->score = &score;
			block[n]->setPosition(i * 43, j * 20);
			block[n]->x = i;
			block[n]->y = j;
			n++;
		}
	}
	do {
		sBall[0].dx = rand()%9-4;
	} while (sBall[0].dx == 0);
	do {
		sBall[0].dy = rand() % 9 - 4;
	} while (sBall[0].dy == 0);
	sBall[0].x = 300;
	sBall[0].y = 300;

	do {
		sBall[1].dx = rand() % 9 - 4;
	} while (sBall[1].dx == 0);
	do {
		sBall[1].dy = rand() % 9 - 4;
	} while (sBall[1].dy == 0);
	sBall[1].x = 300;
	sBall[1].y = 300;
}



void Game::InitSDL() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());

	Uint32 flagsW = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

	window = SDL_CreateWindow("Arkanoid!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GS_width, GS_height, flagsW);
  if (!window)
		printf("SDL window not Create! SDL Error: %s\n", SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		printf("SDL Render not Create! SDL Error: %s\n", SDL_GetError());
}


void Game::Play() {

	while (GameLoop) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // цвет обнуления экрана черный
		SDL_RenderClear(renderer);
		Update();
	  Render();
		
		//you won!
		if (CheckWin())
			GameLoop = false;
	}
}

void Game::Update() {

	managerinput.Update(event);

	if (managerinput.exit)
		GameLoop = false;

	for (int ballnum = 0; ballnum < 2; ++ballnum) {

		if (sBall[ballnum].isActive == true) {

			sBall[ballnum].x += sBall[ballnum].dx;
			//ball strikes block from the side
			for (int i = 0; i < n; i++) {
				SDL_Rect a = { sBall[ballnum].x + 3, sBall[ballnum].y + 3, 6, 6 };
				SDL_FRect b = block[i]->getRect();
				SDL_Rect c = { b.x,b.y,b.w,b.h };
				if (SDL_HasIntersection(&a, &c)) {
					block[i]->DoAction();

					// check if bonus was dropped
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

					//check if healthy block was damaged;
					if (isBlockDamaged == true) {
						isBlockDamaged = false;
						if (block[i]->health == 2)
							block[i]->setTexture(managertexture.getTexture("block05_life2.png"));
						else if (block[i]->health == 1)
							block[i]->setTexture(managertexture.getTexture("block05_life1.png"));
						block[i]->setPosition(block[i]->x * 43, block[i]->y * 20);
					}

					if (sBall[ballnum].dx > 0)
						sBall[ballnum].x -= 6;
					else if (sBall[ballnum].dx < 0)
						sBall[ballnum].x += 6;

					sBall[ballnum].dx = -sBall[ballnum].dx;
				}
			}

			sBall[ballnum].y += sBall[ballnum].dy;
			//ball strikes block from up/down
			for (int i = 0; i < n; i++) {
				SDL_Rect a = { sBall[ballnum].x + 3, sBall[ballnum].y + 3, 6, 6 };
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

					//check is healthy block was damaged;
					if (isBlockDamaged == true) {
						isBlockDamaged = false;
						if (block[i]->health == 2)
							block[i]->setTexture(managertexture.getTexture("block05_life2.png"));
						else if (block[i]->health == 1)
							block[i]->setTexture(managertexture.getTexture("block05_life1.png"));
						block[i]->setPosition(block[i]->x * 43, block[i]->y * 20);
					}

					if (sBall[ballnum].dy > 0)
						sBall[ballnum].y -= 6;
					else if (sBall[ballnum].dy < 0)
						sBall[ballnum].y += 6;

					sBall[ballnum].dy = -sBall[ballnum].dy;
				}
			}

			//check if ball went out from screen
			if (sBall[ballnum].x < 0 || sBall[ballnum].x>520)
				sBall[ballnum].dx = -sBall[ballnum].dx;
			if (sBall[ballnum].y < 0)
				sBall[ballnum].dy = -sBall[ballnum].dy;
			if (sBall[ballnum].y > 450) { //ball was lost
				sBall[ballnum].x = 300;
				sBall[ballnum].y = 300;
				do {
					sBall[ballnum].dx = rand() % 9 - 4;
				} while (sBall[ballnum].dx == 0);
				do {
					sBall[ballnum].dy = rand() % 9 - 4;
				} while (sBall[ballnum].dy == 0);
				sBall[ballnum].isActive = false;
				
				//all balls were lost
				if (sBall[0].isActive == false && sBall[1].isActive == false) {
					isMagnetActivated = false;
					score -= 10;
					sBall[0].isActive = true;
					do {
						sBall[0].dx = rand() % 7 - 3;
					} while (sBall[0].dx == 0);
					do {
						sBall[0].dy = rand() % 7 - 3;
					} while (sBall[0].dy == 0);
				}
			}

			if (managerinput.isKeyDown(SDLK_RIGHT)) {
				if (isMagnetActivated == true && sBall[ballnum].dy == 0 && sBall[ballnum].dx == 0)
					sBall[ballnum].x += 6;
			}
			if (managerinput.isKeyDown(SDLK_LEFT)) {
				if (isMagnetActivated == true && sBall[ballnum].dy == 0 && sBall[ballnum].dx == 0)
					sBall[ballnum].x += (-6);
			}

			//intersection ball and bonuses with paddles
			SDL_Rect a = { sBall[ballnum].x, sBall[ballnum].y, 12, 12 };
			SDL_FRect b = sPaddle.getRect();
			SDL_Rect c = { b.x,b.y,b.w,b.h };
			if (SDL_HasIntersection(&a, &c)) {
				if (isMagnetActivated == true) {

					if (sBall[ballnum].dx)
						sBall[ballnum].dxToRemember = sBall[ballnum].dx;
					if(sBall[ballnum].dy)
						sBall[ballnum].dyToRemember = sBall[ballnum].dy;
					sBall[ballnum].dx = 0; //ball will not move without paddle
					sBall[ballnum].dy = 0;
				}

				else {
					//new speed
					sBall[ballnum].dxToRemember = sBall[ballnum].dx;
					sBall[ballnum].dyToRemember = sBall[ballnum].dy;
					sBall[ballnum].dy = -(rand() % 4 + 2);
					sBall[ballnum].dx = (int)sqrt(sBall[ballnum].dxToRemember * sBall[ballnum].dxToRemember + sBall[ballnum].dyToRemember * sBall[ballnum].dyToRemember - sBall[ballnum].dy * sBall[ballnum].dy);

					if (abs(sBall[ballnum].dx)<2 )
						sBall[ballnum].dx = 2;
					sBall[ballnum].dx = (sBall[ballnum].dxToRemember > 0) ? abs(sBall[ballnum].dx) : -abs(sBall[ballnum].dx);

				}

			}


			//with secondPaddle
			if (secondPaddleIsActive == true) {

				SDL_FRect b2 = secondPaddle.getRect();
				SDL_Rect c2 = { b2.x,b2.y,b2.w,b2.h };

				if (SDL_HasIntersection(&a, &c2)) {

					sBall[ballnum].dxToRemember = sBall[ballnum].dx;
					sBall[ballnum].dyToRemember = sBall[ballnum].dy;
					sBall[ballnum].dy = -(rand() % 4 + 2);
					sBall[ballnum].dx = (int)sqrt(sBall[ballnum].dxToRemember * sBall[ballnum].dxToRemember + sBall[ballnum].dyToRemember * sBall[ballnum].dyToRemember - sBall[ballnum].dy * sBall[ballnum].dy);

					if (abs(sBall[ballnum].dx) < 2)
						sBall[ballnum].dx = 2;
					sBall[ballnum].dx = (sBall[ballnum].dxToRemember > 0) ? abs(sBall[ballnum].dx) : -abs(sBall[ballnum].dx);

					secondPaddleIsActive = false;
				}
			}

			//release ball from magnet
			if (managerinput.isKeyDown(SDLK_SPACE) && sBall[ballnum].dy == 0 && sBall[ballnum].dx == 0 && isMagnetActivated == true) {
				sBall[ballnum].dy = -(rand() % 4 + 2);
				sBall[ballnum].dx = (int)sqrt(sBall[ballnum].dxToRemember * sBall[ballnum].dxToRemember + sBall[ballnum].dyToRemember * sBall[ballnum].dyToRemember - sBall[ballnum].dy * sBall[ballnum].dy);

				if (abs(sBall[ballnum].dx) < 2)
					sBall[ballnum].dx = 2;
				sBall[ballnum].dx = (sBall[ballnum].dxToRemember > 0) ? abs(sBall[ballnum].dx) : -abs(sBall[ballnum].dx);
			}

		} //if ball is active
	} //for 2 balls

	SDL_FPoint pos = sPaddle.getPosition();
	if (managerinput.isKeyDown(SDLK_RIGHT) && pos.x < 430) 
		sPaddle.move(6, 0);
	if (managerinput.isKeyDown(SDLK_LEFT) && pos.x > 0) 
		sPaddle.move(-6, 0);
	


	//check possible strike between 2 balls
	if (sBall[0].isActive == true && sBall[1].isActive == true) {

		SDL_Rect b1 = { sBall[0].x, sBall[0].y , 12, 12 };
		SDL_Rect b2 = { sBall[1].x, sBall[1].y, 12, 12 };

		if (SDL_HasIntersection(&b1, &b2)) {
			sBall[0].dx = -sBall[0].dx;
			sBall[1].dx = -sBall[1].dx;
			sBall[0].dy = -sBall[0].dy;
			sBall[1].dy = -sBall[1].dy;
		}


	}

	//check if bonuses hit paddle
	for (int i = 0; i < bonusSize; ++i) {
		if (bonuses[i]->isFalling == true) {

			SDL_Rect bonus = { bonuses[i]->x, bonuses[i]->y, 42, 42 };
			SDL_FRect b = sPaddle.getRect();
			SDL_Rect c = { b.x,b.y,b.w,b.h };

			//intersection between bonus and first paddle
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

				//check if second paddle was created
				if (secondPaddleWasCreated == true) {
					secondPaddleWasCreated = false;
					secondPaddleIsActive = true;
					if (paddleSize == 1)
						secondPaddle.setTexture(managertexture.getTexture("paddle_size1.png"));
					else if (paddleSize == 2)
						secondPaddle.setTexture(managertexture.getTexture("paddle_size2.png"));
					else if (paddleSize == 3)
						secondPaddle.setTexture(managertexture.getTexture("paddle_size3.png"));
					else if (paddleSize == 4)
						secondPaddle.setTexture(managertexture.getTexture("paddle_size4.png"));
					else if (paddleSize == 5)
						secondPaddle.setTexture(managertexture.getTexture("paddle_size5.png"));
					secondPaddle.setPosition(rand() % 340, 440);
				}
				
			}


		}
	}

	sBall[0].setPosition(sBall[0].x, sBall[0].y);
	sBall[1].setPosition(sBall[1].x, sBall[1].y);

	//bonus falling animation
	for (int i = 0; i < bonusSize; ++i) {
		if (bonuses[i]->isFalling == true) {
			bonuses[i]->y += bonuses[i]->dy;
			bonuses[i]->setPosition(bonuses[i]->x, bonuses[i]->y);
		}
	}
	
}

void Game::Render() {

	sBackground.draw(renderer);

	if(sBall[0].isActive == true)
	  sBall[0].draw(renderer);
	if(sBall[1].isActive == true)
		sBall[1].draw(renderer);

	sPaddle.draw(renderer);

	for (int i = 0; i < bonusSize; ++i) {
		if(bonuses[i]->isFalling == true)
		   bonuses[i]->draw(renderer);
	}
	for (int i = 0; i < n; i++)
		block[i]->draw(renderer);

	if (secondPaddleIsActive == true)
		secondPaddle.draw(renderer);
	
	SDL_RenderPresent(renderer);
}

int Game::FindBonusInVector(int i, int j) {
	for (int k = 0; i < bonusSize; ++k) {
		if (bonuses[k]->x == i && bonuses[k]->y == j)
			return k;
	}
	return -1;
}

bool Game::CheckWin() {
	const int UNDESTROYABLE = 1;
	for (int i = 0; i < n; ++i) {
		SDL_FPoint pos = block[i]->getPosition();
		if (pos.x!=(-100) && block[i]->kind != UNDESTROYABLE)
			return false;
	}
	std::cout << "You won!\n";
	return true;
}