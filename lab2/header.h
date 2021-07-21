#pragma once
#include <iostream>
#include <cmath>
#include <random> //random desides if solution by average student coorect of not
#include <queue>  //letters
#include <list>   //table of scores
using namespace std;
#define INF 123456 //means that all numbers are solutions of equation 0x^2+0x+0=0
#define NAMESIZE 30

class Equation {
public:
  double a, b, c; //coefs
  int numOfAns; //amount of answers
  double ans[2]; //answers

  Equation();
  Equation(double a, double b, double c);

  //solving correctly
  void SolveTaskCorrectly();
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

  Human(string str);
  ~Human();
  void ReadTask(const char* str);
};

//solves equation right
class Teacher : public Human {
private:
  queue <Letter> queue_of_letters;
  list <Mark> table;
public:
  Teacher(const char* str);
  ~Teacher();
  
  void SolveTaskCorrectly();
  void ReceiveLetter(Letter& letter);

  void CheckLetters();
  void PublishTable();
};


class Student : public Human{
public:
  Student(string str);
  ~Student();
  void SendLetter(Teacher& teacher) const;
};

//solves
class GoodStudent :public Student {
public:
  GoodStudent(const char* str);
  ~GoodStudent();
  void SolveTask();
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