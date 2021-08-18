#include "Block.h"

//block deletes itself
void UsualBlock::DoAction(){
  setPosition(-100, 0);
}

//does nothing
void NonDestroyableBlock::DoAction(){}

//drops some bonus
void BonusBlock::DoAction(){

  // drop bonus which belongs to this block
  for (int i = 0; i < (*bonusSize); ++i) {
    if (x == (*arr)[i]->x && y == (*arr)[i]->y) {
      (*arr)[i]->isDropped = true;
      break;
    }
  }

  setPosition(-100, 0);
}

//changes speed
void ChangeSpeedBlock::DoAction(){
  if (rand() % 2) {
    ball->dx++;
    ball->dy++;
  }
  else {
    ball->dx--;
    ball->dy--;
  }
  setPosition(-100, 0);
}

void HealthyBlock::DoAction(){
  health--;
  if(health==0)
    setPosition(-100, 0);
}