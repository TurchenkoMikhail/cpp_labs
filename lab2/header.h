#pragma once
#include <iostream>
#include <cmath>
#include <random> //random desides if solution by average student coorect of not
#include <queue>  //letters
#include <list>   //table of scores
using namespace std;
#define INF 123456 //means that all numbers are solutions of equation 0x^2+0x+0=0
#define NAMESIZE 50
#pragma warning(disable:4996)

typedef struct {
  double a, b, c;
}task_t;

typedef struct {
  int num; //amount of answers
  double ans[2];
}answer_t;

//letter
typedef struct {
  task_t* tasks;//array of tasks
  answer_t* ans;
  string name;  //students name
}letter_t;

typedef struct {
  string name; //student
  int score;
}mark_t;


class Human {
public:
  string name;
  task_t* task;    //array of quadratic equations
  answer_t* answer;//array of answers on equations
  int len;         //amount of equations (== amount of answers)

  Human(const char* str);
  ~Human();
  void ReadTask(const char* str);
  void SolveTask(); //solves equation right
};

class Student : public Human{
public:
  Student(const char* str);
  ~Student();
  void SendLetter();
};

//solves
class GoodStudent :public Student {
public:
  GoodStudent(const char* str);
  ~GoodStudent();
  //solves equation right
};

class AverageStudent : public Student {
public:
  AverageStudent(const char* str);
  ~AverageStudent();
  void SolveTask();
};

class BadStudent : public Student {
public:
  BadStudent(const char* str);
  ~BadStudent();
  void SolveTask();
};

class Teacher : public Human {
public:
  Teacher(const char* str);
  ~Teacher();

  //solves equation right
  void CheckLetterFromQueue();
  void PublishTable();
};

//for good, lucky average students and teacher
answer_t SolveLinear(double b, double c);
answer_t SolveQuadratic(double a, double b, double c);