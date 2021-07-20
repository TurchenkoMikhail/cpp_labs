#include "header.h"

Student::Student(string str): Human(str) {}
Student::~Student() {}

GoodStudent::GoodStudent(const char* str): Student(str) {}
AverageStudent::AverageStudent(const char* str): Student(str){}
BadStudent::BadStudent(const char* str): Student(str){}

GoodStudent::~GoodStudent() {}
AverageStudent::~AverageStudent() {}
BadStudent::~BadStudent() {}

void Student::SendLetter(Teacher& teacher) {
  if (!tasks)
    return;

  Letter letter;
  letter.tasks = tasks;
  letter.name = name;

  teacher.ReceiveLetter(letter);
}

void GoodStudent::SolveTask() {
  if (!tasks) //if there are now tasks yet
    return;
  for (int i = 0; i < len; i++)
    tasks[i].SolveTaskCorrectly();
}

void AverageStudent::SolveTask() {
  if (!tasks) //if there are now tasks yet
    return;
  for (int i = 0; i < len; i++) {
    if (rand() % 2) {  //bad solution
      tasks[i].numOfAns = 1;
      tasks[i].ans[0] = 0;
    }
    else //good solution
      tasks[i].SolveTaskCorrectly();
  }
}

void BadStudent::SolveTask() {
  if (!tasks) //if there are now tasks yet
    return;

  //if bad student, every equation has only one answer - zero
  for (int i = 0; i < len; i++){
    tasks[i].numOfAns = 1;
    tasks[i].ans[0] = 0;
  }
}