#include <iostream>
#include <cmath>
using namespace std;

#define INF 123456 //all answers are solutions

typedef struct {
  int num; //amount of answers
  double ans[2];
}answer_t;

void Scan(double* a, double* b, double* c) {
  cin >> *a >> *b >> *c;
}

answer_t SolveLinear(double b, double c) {
  answer_t ans;
// equation 0x = 0
  if (b == 0.0 && c == 0.0)
    ans.num = INF;

  else if (b == 0.0 && c != 0.0)
    ans.num = 0;
  else { //b!=0
    ans.num = 1;
    ans.ans[0] = -c / b;
  }
  return ans;
}

answer_t SolveQuadratic(double a, double b, double c) {
  answer_t ans;
  double d = b * b - 4.0 * a * c;
  double discr;
  if (d > 0.0) {
    discr = sqrt(d);
    ans.num = 2;
    ans.ans[0] = (-b - discr) / (2.0 * a);
    ans.ans[1] = (-b + discr) / (2.0 * a);
  }
  else if (d == 0.0) {
    ans.num = 1;
    ans.ans[0] = -b / (2 * a);
  }
  else
    ans.num = 0;
  return ans;
}

void PrintAnswer(answer_t* ans) {
  if (ans->num == 0)
    cout << "no solution" << endl;
  else if (ans->num == 1)
    cout << ans->ans[0] << endl;
  else if (ans->num == 2)
    cout << ans->ans[0] << " " << ans->ans[1] << endl;
  else //infinite amount of numbers
    cout << "All numbers are solutions";
}

int main(void) {
  answer_t ans;
  double a, b, c;
  Scan(&a, &b, &c);

  if (a == 0.0)
    ans=SolveLinear(b, c);

  else
    ans=SolveQuadratic(a, b, c);
  
  PrintAnswer(&ans);
  return 0;
}