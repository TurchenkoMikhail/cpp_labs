#pragma once
#include "SDL_Sprite.h"
#include "Ball.h"

class Bonus : public SDL_Sprite{
public:
  Bonus() { isFalling = false; isDropped = false; dy = 2; }
  virtual void IsActivated() = 0;
  bool isFalling, isDropped;
  int x, y, dy;
};

class BonusBiggerCarriageSize : public Bonus {
public:
  bool* isPaddleResized;
  int* paddleSize;
  void IsActivated();
};

class BonusSmallerCarriageSize : public Bonus {
public:
  bool* isPaddleResized;
  int* paddleSize;
  void IsActivated();
};

class BoostSpeed : public Bonus {
public:
  Ball* ball;
  void IsActivated();
};

class DecreaseSpeed : public Bonus {
public:
  Ball* ball;
  void IsActivated();
};

class Magnet : public Bonus {
public:
  void IsActivated();
};

class SecondCarriage : public Bonus {
public:
  void IsActivated();
};

class ChangePathBall : public Bonus {
public:
  void IsActivated();
};

class SecondBall : public Bonus {
public:
  void IsActivated();
};