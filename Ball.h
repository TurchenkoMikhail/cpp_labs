#pragma once
#include "SDL_Sprite.h"

class Ball : public SDL_Sprite {
public:
  int x, y, dx, dy;
  int dxToRemember, dyToRemember;
  bool isActive;
};