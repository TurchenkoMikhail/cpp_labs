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

//TO DO
void Magnet::IsActivated() {
  std::cout << "Dropped magnet!";
}
void SecondCarriage::IsActivated() {
  std::cout << "Dropped second carriage!\n";
}
void ChangePathBall::IsActivated() {
  std::cout << "Dropped new path!\n";
}
void SecondBall::IsActivated() {
  std::cout << "Dropped second ball!\n";
}
