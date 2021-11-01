#include "Bonus.h"

bool Bonus::Destroy(std::vector<gemsToDoAction>& arr) {

	//delete gem
	if (GetAlpha() > 10) {
		DecreaseAlpha();
		return true;
	}
	//do bonus's action
	else {
		BonusAction(arr);
		return false;
	}

}

void Bomb::BonusAction(std::vector<gemsToDoAction>& arr) {
	//bomb deletes itself and 4 stones from all map

	std::vector<gemsToDoAction> arr1;
	gemsToDoAction temp;

	bool exist;

	//choosing gems
	for (int i = 0; i < 4; i++) {

		do {
			exist = false;

			temp.first = rand() % 8 + 1; //random in [1, 8]
			temp.second = rand() % 8 + 1;
			temp.type = GetKind();
			arr1.push_back(temp);

			for (int j = 0; j < i; j++) {
				if (arr1[i].first == arr1[j].first && arr1[i].second == arr1[j].second) {
					arr1.pop_back();
					exist = true;
					break;
				}
			}
		} while (exist == true);
	}

	for (int i = 0; i < arr1.size(); ++i)
		arr.push_back(arr1[i]);

}
void Recolor::BonusAction(std::vector<gemsToDoAction>& arr) {
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
	//IncreaseMatch();

	std::pair<int, int> vec[50];
	gemsToDoAction p1, p2;

	int size = 0;
	for (int i1 = -3; i1 <= 3; i1++) { //row
		for (int j1 = -3; j1 <= 3; j1++) { //col

			//if it is in 3-gem-radius except neighbour
			if ((abs(i1) + abs(j1) >= 2) && ((abs(i1) + abs(j1) <= 3))) {
				if ((GetRow() + i1 >= 1 && GetRow() + i1 <= 8) && (GetCol() + j1 >= 1 && GetCol() + j1 <= 8))
					vec[size++] = { GetRow() + i1, GetCol() + j1 };
			}

		}
	}
	int choice = rand() % size;
	p1.first = vec[choice].first;
	p1.second = vec[choice].second;
	do {
		choice = rand() % size;
		p2.first = vec[choice].first;
		p2.second = vec[choice].second;
	} while (p1.first == p2.first && p1.second == p2.second);

	p1.type = GetKind();
	p1.kindToRemember = GetKindToRem();
	p2.type = GetKind();
	p2.kindToRemember = GetKindToRem();
	arr.push_back(p1);
	arr.push_back(p2);
}

void Recolor::SetKindToRem(int _kind) { kindToRemember = _kind; }
int Recolor::GetKindToRem() { return kindToRemember; }