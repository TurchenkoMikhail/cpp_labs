#include <iostream>
#include <cmath>
using namespace std;

void Scan(double* a, double* b, double* c) {
  cin >> *a >> *b >> *c;
}

void SolveLinear(double b, double c) {
  if (b == 0.0 && c == 0.0) // equation 0x = 0
    cout << "all";
  else if (b == 0.0 && c != 0.0)
    cout << "no solution";
  else //b!=0
    cout << -c / b;
}

void SolveQuadratic(double a, double b, double c) {
  double d = b * b - 4.0 * a * c;

  if (d >= 0.0) {
    double discr = sqrt(d);
    cout << (-b + discr) / (2.0 * a) << " " << (-b - discr) / (2.0 * a);
  }
  else
    cout << "no solution";
}

int main(void) {
  double a, b, c;
  Scan(&a, &b, &c);

  if (a == 0.0)
    SolveLinear(b, c);

  else
    SolveQuadratic(a, b, c);
  
  return 0;
}