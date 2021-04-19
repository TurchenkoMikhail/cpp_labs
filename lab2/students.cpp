#include "header.h"

extern queue <letter_t> queue_of_letters;

Student::Student(const char* str)
  :Human(str)
{}

Student::~Student() {
  if (task) {
    delete[] task;
    task = NULL;
  }
  if (answer) {
    delete[] answer;
    answer = NULL;
  }
}

GoodStudent::GoodStudent(const char* str)
  : Student(str) 
{}

AverageStudent::AverageStudent(const char* str)
  : Student(str)
{}

BadStudent::BadStudent(const char* str)
  : Student(str)
{}


GoodStudent::~GoodStudent() {
  if (task) {
    delete[] task;
    task = NULL;
  }
  if (answer) {
    delete[] answer;
    answer = NULL;
  }
}

AverageStudent::~AverageStudent() {
  if (task) {
    delete[] task;
    task = NULL;
  }
  if (answer) {
    delete[] answer;
    answer = NULL;
  }
}

BadStudent::~BadStudent() {
  if (task) {
    delete[] task;
    task = NULL;
  }
  if (answer) {
    delete[] answer;
    answer = NULL;
  }
}

void Student::SendLetter() {
  if (!answer)
    return;

  letter_t letter;
  letter.tasks = task;
  letter.ans = answer;
  letter.name = name;

  queue_of_letters.push(letter);
}

void AverageStudent::SolveTask() {
  if (!task) //if there are now tasks yet
    return;

  answer = new answer_t[len];
  int i;

  for (i = 0; i < len; i++) {
    if (rand() % 2) { //bad solution
      answer[i].num = 1;
      answer[i].ans[0] = 0.0;
    }
    else { //good solution
      if (task[i].a == 0.0)
        answer[i] = SolveLinear(task[i].b, task[i].c);
      else
        answer[i] = SolveQuadratic(task[i].a, task[i].b, task[i].c);
    }
  }
}

void BadStudent::SolveTask() {
  if (!task) //if there are now tasks yet
    return;

  answer = new answer_t[len];
  int i;

  //if bad student, every equation has only one answer - zero
  for (i = 0; i < len; i++) {
    answer[i].num = 1;
    answer[i].ans[0] = 0.0;
  }
}