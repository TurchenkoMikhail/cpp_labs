#include "Bonus.h"
#include <iostream>

void BonusBiggerCarriageSize::IsActivated(){
  if ((*paddleSize) < 5) {
    (*paddleSize)++;
    (*isPaddleResized) = true;
  }
}
void BonusSmallerCarriageSize::IsActivated() {
  if ((*paddleSize) > 1) {
    (*paddleSize)--;
    (*isPaddleResized) = true;
  }
}

void BoostSpeed::IsActivated() {
  if (abs(ball->dx) < 6) 
    ball->dx = (ball->dx > 0) ? ball->dx + 1 : ball->dx - 1;
  
  if (abs(ball->dy) < 5)
    ball->dy = (ball->dy > 0) ? ball->dy + 1 : ball->dy - 1;
}

void DecreaseSpeed::IsActivated() {
  if (abs(ball->dx) > 2)
    ball->dx = (ball->dx > 0) ? ball->dx - 1 : ball->dx + 1;
  if (abs(ball->dy) > 1)
    ball->dy = (ball->dy > 0) ? ball->dy - 1 : ball->dy + 1;
}


void Magnet::IsActivated() { (*isMagnetActivated) = true;}

void SecondCarriage::IsActivated() {
  if (*secondPaddle == nullptr) {
    *secondPaddle = new SDL_Sprite;
    *secondPaddleWasCreated = true;
  }
}
void ChangePathBall::IsActivated() {
  do {
    ball->dx = rand() % 11 - 5; //[-5, 5]
  } while (ball->dx == 0);
  do {
    ball->dy = rand() % 11 - 5; //[-5, 5]
  } while (ball->dy == 0);
}
void SecondBall::IsActivated() {
  std::cout << "Dropped second ball!\n";
}
