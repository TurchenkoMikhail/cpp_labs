#include "Score.h"

Score::Score() { x = 0, y = 0, score = 0; }
void Score::Initialize(int _x, int _y) { x = _x; y = _y; score = 0; }
void Score::AppendScore(int count) { score += count; }
int Score::GetScore() { return score; }
int Score::GetX() { return x; }
int Score::GetY() { return y; }