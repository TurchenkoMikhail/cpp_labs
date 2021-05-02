#pragma once
#include <iostream>
#include <cmath>
#include <random> //random desides if solution by average student coorect of not
#include <queue>  //letters
#include <list>   //table of scores
using namespace std;
#define INF 123456 //means that all numbers are solutions of equation 0x^2+0x+0=0
#define NAMESIZE 50

class Equation {
public:
  double a, b, c; //coefs
  int numOfAns; //amount of answers
  double ans[2]; //answers

  Equation();
  Equation(double a, double b, double c);

  //solving correctly
  void SolveLinear();
  void SolveQuadratic();

  //solving badly
  void SolveBadly(); // one ans - zero
};

class Letter {
public:
  Equation* tasks; //array of tasks and answers in letter
  string name;
};

class Mark {
public:
  string name;
  int score;

  Mark();
  Mark(const char* str, int count);
};

class Human {
public:
  string name;
  Equation *tasks;
  int len;         //amount of equations (== amount of answers)

  Human(const char* str);
  ~Human();
  void ReadTask(const char* str);
  void SolveTask(); //solves equation right
};

class Teacher : public Human {
public:

  Teacher(const char* str);
  ~Teacher();

  //solves equation right
  void CheckLetterFromQueue(queue <Letter>* queue_of_letters, list <Mark>* table);
  void PublishTable(list <Mark> *table);
};


class Student : public Human{
public:
  Student(const char* str);
  ~Student();
  void SendLetter(queue <Letter> *queue_of_letters);
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