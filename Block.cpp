#include "Block.h"

//block deletes itself
void UsualBlock::DoAction(){
  (*score)++;
  setPosition(-100, 0);
}

//does nothing
void NonDestroyableBlock::DoAction() { (*score)++; }

//drops some bonus
void BonusBlock::DoAction(){
  (*score)++;

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

  (*score)++;

  if (rand() % 2) {
    ball[0]->dx++;
    ball[0]->dy++;
    ball[1]->dx++;
    ball[1]->dy++;
  }
  else {
    if(ball[0]->dx > 2)
      ball[0]->dx--;
    if (ball[0]->dy > 2)
      ball[0]->dy--;
    if (ball[1]->dx > 2)
      ball[1]->dx--;
    if (ball[1]->dy > 2)
      ball[1]->dy--;
  }
  setPosition(-100, 0);
}

void HealthyBlock::DoAction(){
  (*score)++;
  health--;
  if (health == 0) {
    setPosition(-100, 0);
    return;
  }
  (*isBlockDamaged) = true;
}