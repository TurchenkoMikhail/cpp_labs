#pragma once
#include <iostream>
#include "Piece.h"

class Cell {
public:
	int x, y, col, row, kind, match, alpha;
	std::shared_ptr <Cell> (*grid)[10]; //ptr to grid to allow bonuses do specific tasks
	Cell();
	~Cell();
	virtual void DoSpecificAction() = 0;
};

class Gem : public Cell {
public:
	void DoSpecificAction(); //gem does nothing
};

class Bomb : public Cell {
public:
	void DoSpecificAction();
};

class Recolor : public Cell {
public:
	int kindToRemember;
	void DoSpecificAction();
};
