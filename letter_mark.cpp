#include "header.h"

Mark::Mark() { score = 0; }

Mark::Mark(const char* str, int count) {
  name = string(str);
  score = count;
}

Equation::Equation() {
  a = 0; b = 0; c = 0; numOfAns = 0; ans[0] = 0; ans[1] = 0;
}

Equation::Equation(double a0, double b0, double c0) {
  a = a0; b = b0; c = c0; numOfAns = 0; ans[0] = 0; ans[1] = 0;
}