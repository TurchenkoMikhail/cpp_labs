#include "Bonus.h"
#include <iostream>

void BonusBiggerCarriageSize::IsActivated(){
  (*score)++;
  if ((*paddleSize) < 5) {
    (*paddleSize)++;
    (*isPaddleResized) = true;
  }
}
void BonusSmallerCarriageSize::IsActivated() {
  (*score)++;
  if ((*paddleSize) > 1) {
    (*paddleSize)--;
    (*isPaddleResized) = true;
  }
}

void BoostSpeed::IsActivated() {
  (*score)++;

  if (abs(ball[0]->dx) < 6)
    ball[0]->dx = (ball[0]->dx > 0) ? (ball[0]->dx + 1) : (ball[0]->dx - 1);
  if (abs(ball[0]->dy) < 5)
    ball[0]->dy = (ball[0]->dy > 0) ? (ball[0]->dy + 1) : (ball[0]->dy - 1);

  if (abs(ball[1]->dx) < 6)
    ball[1]->dx = (ball[1]->dx > 0) ? (ball[1]->dx + 1) : (ball[1]->dx - 1);
  if (abs(ball[1]->dy) < 5)
    ball[1]->dy = (ball[1]->dy > 0) ? (ball[1]->dy + 1) : (ball[1]->dy - 1);
}

void DecreaseSpeed::IsActivated() {

  (*score)++;

<<<<<<< Updated upstream
  if (abs(ball[0]->dx) > 3)
    ball[0]->dx = (ball[0]->dx > 0) ? ball[0]->dx - 1 : ball[0]->dx + 1;
  if (abs(ball[0]->dy) > 3)
    ball[0]->dy = (ball[0]->dy > 0) ? ball[0]->dy - 1 : ball[0]->dy + 1;

  if (abs(ball[1]->dx) > 3)
    ball[1]->dx = (ball[1]->dx > 0) ? ball[1]->dx - 1 : ball[1]->dx + 1;
  if (abs(ball[1]->dy) > 3)
=======
  if (abs(ball[0]->dx) > 2)
    ball[0]->dx = (ball[0]->dx > 0) ? ball[0]->dx - 1 : ball[0]->dx + 1;
  if (abs(ball[0]->dy) > 2)
    ball[0]->dy = (ball[0]->dy > 0) ? ball[0]->dy - 1 : ball[0]->dy + 1;

  if (abs(ball[1]->dx) > 2)
    ball[1]->dx = (ball[1]->dx > 0) ? ball[1]->dx - 1 : ball[1]->dx + 1;
  if (abs(ball[1]->dy) > 2)
>>>>>>> Stashed changes
    ball[1]->dy = (ball[1]->dy > 0) ? ball[1]->dy - 1 : ball[1]->dy + 1;
}


void Magnet::IsActivated() { (*isMagnetActivated) = true; (*score)++;}

void SecondCarriage::IsActivated() {
  (*score)++;
  if (*secondPaddleIsActive == false)
    *secondPaddleWasCreated = true;
}
void ChangePathBall::IsActivated() {
  (*score)++;
  do {
    ball[0]->dx = rand() % 9 - 4; //[-4, 4]
  } while (ball[0]->dx == 0);
  do {
    ball[0]->dy = rand() % 9 - 4; //[-4, 4]
  } while (ball[0]->dy == 0);


  do {
    ball[1]->dx = rand() % 9 - 4; //[-4, 4]
  } while (ball[1]->dx == 0);
  do {
    ball[1]->dy = rand() % 9 - 4; //[-4, 4]
  } while (ball[1]->dy == 0);
}
void SecondBall::IsActivated() {
  (*score)++;
  (*ball)[0].isActive = true;
  (*ball)[1].isActive = true;
}
