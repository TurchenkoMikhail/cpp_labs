#include "Gem.h"

bool Gem::Destroy(std::vector<gemsToDoAction>& arr) {

	//delete gem
	if (GetAlpha() > 10) {
		DecreaseAlpha();
		return true;
	}
	else {
		gemsToDoAction temp;
		temp.type = GetKind(); //puts self coordinates
		temp.first = GetRow();
		temp.second = GetCol();
		arr.push_back(temp);
		return false;
	}

}