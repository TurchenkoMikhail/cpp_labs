#pragma once
#include "Cell.h"

class Bonus :public Cell {
public:
	bool Destroy(std::vector<gemsToDoAction>& arr);
	virtual void BonusAction(std::vector<gemsToDoAction>& arr) = 0;
};

class Bomb : public Bonus {
public:
	void BonusAction(std::vector<gemsToDoAction>& arr);
};

class Recolor : public Bonus {
private:
	int kindToRemember;
public:
	void BonusAction(std::vector<gemsToDoAction>& arr);
	void SetKindToRem(int _kind);
	int GetKindToRem();
};