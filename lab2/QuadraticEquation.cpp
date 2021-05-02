#include "header.h"

void Equation::SolveLinear() {
// equation 0x = 0
  if (b == 0.0 && c == 0.0)
    numOfAns = INF;

  else if (b == 0.0 && c != 0.0)
    numOfAns = 0;
  else { //b!=0
    numOfAns = 1;
    ans[0] = -c / b;
  }
}

void Equation::SolveQuadratic() {
  double d = b * b - 4.0 * a * c;
  double discr;
  if (d > 0.0) {
    discr = sqrt(d);
    numOfAns = 2;
    ans[0] = (-b - discr) / (2.0 * a);
    ans[1] = (-b + discr) / (2.0 * a);
  }
  else if (d == 0.0) {
    numOfAns = 1;
    ans[0] = -b / (2 * a);
  }
  else
    numOfAns = 0;
}

void Equation::SolveBadly() {
  numOfAns = 1;
  ans[0] = 0;
}