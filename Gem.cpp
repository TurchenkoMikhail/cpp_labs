#include "Gem.h"

bool Gem::Destroy(std::vector<gemsToDoAction>& arr) {

	//delete gem
	if (GetAlpha() > 10) {
		DecreaseAlpha();
		return true;
	}
	else
		return false;

}