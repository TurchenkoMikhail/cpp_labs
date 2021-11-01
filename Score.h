#pragma once
class Score {
private:
	int x, y; //координаты
	int score;

public:
	Score();
	void Initialize(int _x, int _y);
	int GetX();
	int GetY();
	void AppendScore(int count);
	int GetScore();
};
