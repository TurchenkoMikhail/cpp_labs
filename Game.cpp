#include "Game.h"
#include  "time.h" //for srand()

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
	window = nullptr;
	SDL_Quit();
}

void Game::Create(int w, int h) {
	srand((unsigned)time(NULL));
	GS_width = w;
	GS_height = h;

	GameLoop = true;

	InitSDL();

	managertexture.SetRender(renderer);

	background.setTexture(managertexture.getTexture("background.png"));
	items.setTexture(managertexture.getTexture("gems.png"));

	//couting clicks on mouse
	click = 0;

	isSwap = false;
	isMoving = false;
	recolorWasDropped = false;
	bombWasDropped = false;

	ts = 54; //size of cell
	offset = { 150, 24 };

	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++){
			Gem* gptr = new Gem;
			std::shared_ptr <Cell> ptr(gptr);
			grid[i][j] = ptr;
			grid[i][j]->grid = grid;

			grid[i][j]->kind = rand() % 7; //only gems, not bonuses
			grid[i][j]->col = j;
			grid[i][j]->row = i;
			grid[i][j]->x = j * ts;
			grid[i][j]->y = i * ts;
		}
	}

	//gems at the side
	for (int i = 0; i < 10; ++i) {
		Gem* gptr1 = new Gem, *gptr2 = new Gem;
		std::shared_ptr <Cell> ptr1(gptr1), ptr2(gptr2);

		grid[0][i] = ptr1;
		grid[9][i] = ptr2;

		grid[0][i]->kind = -1; //system gem
		grid[9][i]->kind = -1;
	}

	for (int j = 1; j <= 8; j++) {
		Gem* gptr1 = new Gem, * gptr2 = new Gem;
		std::shared_ptr <Gem> ptr1(gptr1), ptr2(gptr2);

		grid[j][0] = ptr1;
		grid[j][9] = ptr2;

		grid[j][0]->kind = -1; //system gem
		grid[j][9]->kind = -1;
	}
}

void Game::InitSDL() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)	
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());

	Uint32 flagsW = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

	window = SDL_CreateWindow("Gems!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GS_width, GS_height, flagsW);
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
	}
}

void Game::Update() {

	managerinput.Update(event);

	if (managerinput.exit)
		GameLoop = false;

	if (managerinput.isKeyPressed(SDL_BUTTON_LEFT)){
		if (!isSwap && !isMoving)
			click++;
		pos = { managerinput.getMouseCoords().x - offset.x, managerinput.getMouseCoords().y - offset.y };
	}

	//fisrt gem
	if (click == 1) {
		x0 = pos.x / ts + 1;
		y0 = pos.y / ts + 1;
	}

	//second gem
	else if (click == 2) {
		x = pos.x / ts + 1;
		y = pos.y / ts + 1;

		//if neighbours
		if (abs(x - x0) + abs(y - y0) == 1) {
			Swap( grid[y0][x0], grid[y][x] );

			isSwap = true;
			click = 0;
			recolorWasDropped = false;
			bombWasDropped = false;

		} //if gems are neighbours
		else
			click = 1;
	}

	//поиск
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++){

			//vertical match
			if (grid[i][j]->kind == grid[i + 1][j]->kind && grid[i][j]->kind == grid[i - 1][j]->kind) {
			  for (int n = -1; n <= 1; n++)
				  grid[i + n][j]->match++;
			}
			
			//gorizontal match
			if (grid[i][j]->kind == grid[i][j + 1]->kind && grid[i][j]->kind == grid[i][j - 1]->kind) {
				for (int n = -1; n <= 1; n++)
					grid[i][j + n]->match++;
			}
		}
	}

	//animation
	isMoving = false;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {

			int dx, dy, speed = 4;
			for (int n = 0; n < speed; n++) {
				dx = grid[i][j]->x - grid[i][j]->col * ts;
				dy = grid[i][j]->y - grid[i][j]->row * ts;
				if (dx)
					grid[i][j]->x -= dx / abs(dx);
				if (dy)
					grid[i][j]->y -= dy / abs(dy);
			}
			if (dx || dy)
				isMoving = true;
		}
	}

	//end of moving
	if (!isMoving) {
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {

				if (grid[i][j]->match && grid[i][j]->alpha > 10){
						grid[i][j]->alpha -= 10;
						isMoving = true;
				}

			}
		}
	}

	
	//recoloring neighbours if this bonus dropped
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {

			//if there is match, search for gem in 3-gems-radius for bonus
			if (grid[i][j]->match) {

				//25% chance to drop recolorer (only from gems, not bonuses)
				if (!recolorWasDropped && grid[i][j]->kind!=7 && grid[i][j]->kind !=8 && Chance(25)) {
					std::pair<int, int> p;
					FindGemToMakeBonus(grid[i][j], p);
					Recolor* ptrRecolor = new Recolor;
					//do not make new bonus
					ptrRecolor->kindToRemember = grid[i][j]->kind;
					std::shared_ptr<Cell> new_recolor(ptrRecolor);

					grid[p.first][p.second] = new_recolor;
					grid[p.first][p.second]->alpha = 255;
					grid[p.first][p.second]->row = p.first;
					grid[p.first][p.second]->col = p.second;
					grid[p.first][p.second]->y = p.first * ts;
					grid[p.first][p.second]->x = p.second * ts;
					grid[p.first][p.second]->grid = grid;

					grid[p.first][p.second]->kind = 8;
					grid[p.first][p.second]->match = 0;
				} //dropping recolorer
				recolorWasDropped = true;

				//25% chance to drop bomb
				if (!bombWasDropped && Chance(25)) {

					std::pair<int, int> p;
					FindGemToMakeBonus(grid[i][j], p);
					Bomb* ptrBomb = new Bomb;
					std::shared_ptr<Cell> new_bomb(ptrBomb);
					grid[p.first][p.second] = new_bomb;

					grid[p.first][p.second]->alpha = 255;
					grid[p.first][p.second]->row = p.first;
					grid[p.first][p.second]->col = p.second;
					grid[p.first][p.second]->y = p.first * ts;
					grid[p.first][p.second]->x = p.second * ts;
					grid[p.first][p.second]->grid = grid;

					grid[p.first][p.second]->kind = 7;
				  grid[p.first][p.second]->match = 0;
				}//dropping bomb
				bombWasDropped = true;

			}//if grid[i][j].match


		}
	}//recoloring

	//counting score
	int score = 0;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++)
			score += grid[i][j]->match;
	}

	//swapping gems if no match
	if (isSwap && !isMoving) {
		//if swapping bombs, use it (no matter match or not)
		if (grid[y0][x0]->kind == 7 || (grid[y0][x0]->kind == 8)) {
			grid[y0][x0]->DoSpecificAction();
			isMoving = true;
		}
		if (grid[y][x]->kind == 7 || grid[y][x]->kind == 8) {
			grid[y][x]->DoSpecificAction();
			isMoving = true;
		}
		else if (!score) 
			Swap(grid[y0][x0], grid[y][x]);

		isSwap = false;
	}

	//Updating
	if (!isMoving) {
		for (int i = 8; i > 0; i--) {
			for (int j = 1; j <= 8; j++) {

				if (grid[i][j]->match) {
					for (int n = i; n > 0; n--) {
						if (!grid[n][j]->match) {
							//Swap
							Swap(grid[n][j], grid[i][j]);
							break;
						};
					}
				}

			}
		}

		//updating the field with new gems
		for (int j = 1; j <= 8; j++) {
			for (int i = 8, n = 0; i > 0; i--) {

				if (grid[i][j]->match) {
					Gem* gptr = new Gem; //only gems, not bonuses
					std::shared_ptr <Cell> ptr(gptr);
					grid[i][j] = ptr;
					grid[i][j]->x = j * ts;
					grid[i][j]->col = j;
					grid[i][j]->row = i;
					grid[i][j]->grid = grid;

					grid[i][j]->kind = rand() % 7;
					grid[i][j]->y = -ts * n++; //gems going down from sky
					grid[i][j]->match = 0;
					grid[i][j]->alpha = 255;
				}

			}
		}
	}

}


void Game::Swap(std::shared_ptr<Cell> p1, std::shared_ptr<Cell> p2)
{
	std::swap(p1->col, p2->col);
	std::swap(p1->row, p2->row);

	grid[p1->row][p1->col] = p1;
	grid[p2->row][p2->col] = p2;
}

void Game::Render() {

	background.draw(renderer);

	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			items.setTextureRect({ grid[i][j]->kind * 49, 0, 49, 49 });
			items.setColor({ (Uint8)255, (Uint8)255, (Uint8)255, (Uint8)grid[i][j]->alpha });
			items.setPosition(grid[i][j]->x, grid[i][j]->y);
			items.move(offset.x - ts, offset.y - ts);
			items.draw(renderer);
		}
	}

	SDL_RenderPresent(renderer);
}

//chance in percents from 0 to 100
bool Game::Chance(int chance) {
	return rand()%100 > (99-chance) ? true : false;
}

void Game::FindGemToMakeBonus(std::shared_ptr<Cell> p, std::pair<int, int>& p1) {
	//gems in radius 3:
	/*          X
	*          XXX
	*         XXXXX
	*        XXXOXXX
	*         XXXXX
	*          XXX
	*           X
	*/
	std::pair<int, int> vec[50];
	int size = 0;
	for (int i1 = -3; i1 <= 3; i1++) { //row
		for (int j1 = -3; j1 <= 3; j1++) { //col

			if ((abs(i1)+abs(j1)>0) && (abs(i1)+abs(j1)<=3)){
				if ((p->row + i1 >= 1 && p->row + i1 <= 8) && (p->col + j1 >= 1 && p->col + j1 <= 8))
					vec[size++] = { p->row + i1, p->col + j1 };
			}

		}
	}
	do {
		p1 = vec[rand() % size];
	} while (grid[p1.first][p1.second]->kind == 7 || grid[p1.first][p1.second]->kind == 8);
}
