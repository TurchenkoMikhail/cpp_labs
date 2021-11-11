#include "Cell.h"

Cell::Cell() { match = 0; alpha = 255;  x = 0; y = 0; row = 0; col = 0; kind = NONE;}
Cell::~Cell(){}

void Cell::Initialize(int _kind, int _x, int _y, int _col, int _row, int _match, int _alpha) {
	kind = (cellType_t)_kind; x = _x; y = _y; col = _col; row = _row; match = _match, alpha = _alpha;
}

int Cell::GetX() const { return x; }
void Cell::DecreaseX(int dx) { x -= (dx / abs(dx)); }
int Cell::GetY() const { return y; }
void Cell::DecreaseY(int dy) { y -= (dy / abs(dy)); }
void Cell::SetCol(int _col) { col = _col; }
int Cell::GetCol() const { return col; }
void Cell::SetRow(int _row) { row = _row; }
int Cell::GetRow() const { return row; }
cellType_t Cell::GetKind() const { return kind; }
void Cell::SetKind(int _kind) { kind = (cellType_t)_kind; }
int Cell::GetMatch() const { return match; }
void Cell::IncreaseMatch() { match = 1; }
int Cell::GetAlpha() const { return alpha; }
void Cell::DecreaseAlpha() { alpha -= 10; }
