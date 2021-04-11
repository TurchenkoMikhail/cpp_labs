#pragma once
#include <iostream>
#include <cmath>
#include <random>
using namespace std;
#define INF 123456 //means that all numbers are solutions of Quadratic Equation
#define NAMESIZE 50

typedef struct {
  double a, b, c;
}task_t;

typedef struct {
  int num; //amount of answers
  double ans[2];
}answer_t;

typedef enum rate_t {
  GOOD,
  AVERAGE,
  BAD,
}rate_t; //type of students

//for good students (and lucky average students)
answer_t SolveLinear(double b, double c);
answer_t SolveQuadratic(double a, double b, double c);

void PrintAnswers(answer_t* ans);