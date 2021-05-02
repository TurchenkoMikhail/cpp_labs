#include "header.h"

Student::Student(const char* str)
  :Human(str)
{}

Student::~Student() {}

GoodStudent::GoodStudent(const char* str)
  : Student(str) 
{}

AverageStudent::AverageStudent(const char* str)
  : Student(str)
{}

BadStudent::BadStudent(const char* str)
  : Student(str)
{}

GoodStudent::~GoodStudent() {}

AverageStudent::~AverageStudent() {}

BadStudent::~BadStudent() {}

void Student::SendLetter(queue <Letter> *queue_of_letters) {
  if (!tasks)
    return;

  Letter letter;
  letter.tasks = tasks;
  letter.name = name;

  queue_of_letters->push(letter);
}

void AverageStudent::SolveTask() {
  if (!tasks) //if there are now tasks yet
    return;
  int i;

  for (i = 0; i < len; i++) {
    if (rand() % 2) { //bad solution
      tasks[i].SolveBadly();
    }
    else { //good solution
      if (tasks[i].a == 0.0)
        tasks[i].SolveLinear();
      else
        tasks[i].SolveQuadratic();
    }
  }
}

void BadStudent::SolveTask() {
  if (!tasks) //if there are now tasks yet
    return;

  int i;

  //if bad student, every equation has only one answer - zero
  for (i = 0; i < len; i++) 
    tasks[i].SolveBadly();
}