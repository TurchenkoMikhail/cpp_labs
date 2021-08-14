#include "Piece.h"

Cell::Cell() { match = 0; alpha = 255;  x = 0; y = 0; row = 0; col = 0; kind = 0;}
Cell::~Cell(){}

void Gem::DoSpecificAction() { ; }

void Bomb::DoSpecificAction() {
		//bomb deletes itself and 4 stones from all map

		std::pair<int, int> arr[5];
		int size_arr = 1;
		bool exist;
		arr[0] = { row, col };

		//choosing gems
		for (int i = 1; i < 5; i++, size_arr++) {

			do {
				exist = false;
				arr[i] = { rand() % 8 + 1, rand() % 8 + 1 }; //random in [1, 8]
				for (int j = 0; j < size_arr; j++) {
					if (arr[i] == arr[j]) {
						exist = true;
						break;
					}
				}
			} while (exist == true);
		}

		for (int i = 0; i < 5; i++)
			grid[arr[i].first][arr[i].second]->match = 1;
}

void Recolor::DoSpecificAction() {
	//gems in radius 3:
	//           X
	//          XXX
	//         XNNNX
	//        XXNONXX
	//         XNNNX
	//          XXX
	//           X
  // do not pick 'N' (neighbours)
	//
	
	//bonus deletes itself
	this->match = 1;

	std::pair<int, int> vec[50], p1,p2;
	int size = 0;
	for (int i1 = -3; i1 <= 3; i1++) { //row
		for (int j1 = -3; j1 <= 3; j1++) { //col

			//if it is in 3-gem-radius except neighbour
			if ((abs(i1) + abs(j1) >= 2) && ((abs(i1) + abs(j1) <= 3))) {
				if ((row + i1 >= 1 && row + i1 <= 8) && (col + j1 >= 1 && col + j1 <= 8))
					vec[size++] = { row + i1, col + j1 };
			}

		}
	}
	p1 = vec[rand() % size];
	do {
		p2 = vec[rand() % size];
	} while (p1.first == p2.first && p1.second == p2.second);

	grid[p1.first][p1.second]->kind = kindToRemember;
	grid[p1.first][p1.second]->match = 0;

	grid[p2.first][p2.second]->kind = kindToRemember;
	grid[p2.first][p2.second]->match = 0;
}
