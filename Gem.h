#pragma once
#include "Cell.h"

class Gem : public Cell {
public:
	bool Destroy(std::vector<gemsToDoAction>& arr);
};