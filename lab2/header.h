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

//type of students
typedef enum rate_t {
  GOOD,
  AVERAGE,
  BAD,
}rate_t;

//letter
typedef struct {
  task_t* tasks;     //array of tasks
  answer_t* ans;
  string name;  //students name
}letter_t;

extern queue <letter_t> queue_of_letters;

typedef struct {
  string name; //student
  int score;
}mark_t;

extern list <mark_t> table;

class Student {
private:
  string s_name;
  rate_t s_rate;     //defines is student good, average or bad
  task_t* s_task;    //array of quadratic equations
  answer_t* s_answer;//array of answers on equations
  int s_len;         //amount of equations (== amount of answers)

public:
  Student(const char* name, rate_t rate);
  ~Student();
  void ReadTask(const char* str);
  void SolveTask();
  void SendLetter();
};

class Teacher {
private:
  task_t* t_task;           //array of quadratic equations
  answer_t* t_rightanswers;//array of answers on equations
  int t_len;                //amount of equations (== amount of answers)

public:
  Teacher(void);
  ~Teacher();

  void GetTask(const char* str);
  void GetRightAnswers();
  void CheckLetterFromQueue();
  void PublishTable();
};

//for good students (and lucky average students)
answer_t SolveLinear(double b, double c);
answer_t SolveQuadratic(double a, double b, double c);

void PrintAnswers(answer_t* ans);