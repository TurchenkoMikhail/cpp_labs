#pragma once
#include <iostream>
#include <vector>

typedef struct {
	int first, second;
	int type; //cellType_t
	int kindToRemember;
}gemsToDoAction;

const int AMOUNT_OF_BONUSES = 2;

typedef enum {
	NONE = -1,

	DARK_BLUE,
	DARK_GREEN,
	YELLOW,
	GREEN,
	VIOLET,
	RED,
	BLUE,

	BOMB,
	RECOLOR,

	AMOUNT_OF_ITEMS //initializes automatically
}cellType_t;



class Cell {
private:
	int x, y, col, row, match, alpha;
	cellType_t kind;
public:
	void Initialize(int _kind, int _x, int _y, int _col, int _row, int _match, int _alpha);
	virtual bool Destroy(std::vector<gemsToDoAction>& arrOfGems) = 0; //destroy itself and activate bonus
	Cell();
	~Cell();
	int GetX() const;
	void DecreaseX(int dx);
	int GetY() const;
	void DecreaseY(int dy);
	void SetCol(int _col);
	int GetCol() const;
	void SetRow(int _row);
	int GetRow() const;
	void SetKind(int _kind);
	cellType_t GetKind() const;
	int GetMatch() const;
	void IncreaseMatch();
	int GetAlpha() const;
	void DecreaseAlpha();
};
