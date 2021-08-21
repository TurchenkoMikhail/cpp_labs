#pragma once
#include "SDL_Sprite.h"
#include <iostream>
#include "Ball.h"
#include "Bonus.h"
<<<<<<< Updated upstream
#include <vector>

//typedef SDL_Sprite Block;
=======

>>>>>>> Stashed changes
class Block : public SDL_Sprite {
public:
  int* score;
  int x,y,kind, health;
  virtual void DoAction() = 0;
};

//kind = 0
class UsualBlock : public Block {
public:
  void DoAction();
};

//kind = 1
class NonDestroyableBlock : public Block {
public:
  void DoAction();
};

//kind = 2
class BonusBlock : public Block {
public:
<<<<<<< Updated upstream
  //std::vector <Bonus>* arr;
=======
>>>>>>> Stashed changes
  std::shared_ptr <Bonus> (*arr)[100];
  int* bonusSize;
  void DoAction();
};

//kind = 3
class ChangeSpeedBlock : public Block {
public:
  Ball (*ball)[2];
  void DoAction();
};

//kind = 4
class HealthyBlock : public Block {
public:
  bool* isBlockDamaged;
  HealthyBlock() { health = 3; }
  void DoAction();
};