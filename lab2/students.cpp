#include "header.h"

Student::Student(const char* name, rate_t rate) {
  s_rate = rate;
  s_name = string(name);
  s_task = NULL;
  s_answer = NULL;
  s_len = 0;
}

Student::~Student() {
  if (s_task)
    delete[] s_task;
  if (s_answer)
    delete[] s_answer;
}

void Student::ReadTask(const char* str) {
  FILE* filename = fopen(str, "r");
  if (!filename)
    return;

  int i;
  char c;

  while (!feof(filename)) {
    fscanf(filename, "%c", &c);
    if (c == '\n')
      s_len++;
  }
  s_len--;
  s_task = new task_t[s_len];

  fseek(filename, 0, SEEK_SET);

  for (i = 0; i < s_len; i++)
    fscanf(filename, "%lf%lf%lf", &s_task[i].a, &s_task[i].b, &s_task[i].c);

  fclose(filename);
}

void Student::SolveTask() {

  if (!s_task) //if there are now tasks yet
    return;

  s_answer = new answer_t[s_len];
  int i;

  //if bad student, every equation has only one answer - zero
  if (s_rate == BAD) {
    for (i = 0; i < s_len; i++) {
      s_answer[i].num = 1;
      s_answer[i].ans[0] = 0.0;
    }
  }

  //if average student, answer can be correct or incorrect
  else if (s_rate == AVERAGE) {

    for (i = 0; i < s_len; i++) {
      if (rand() % 2) { //bad solution
        s_answer[i].num = 1;
        s_answer[i].ans[0] = 0.0;
      }
      else { //good solution
        if (s_task[i].a == 0.0)
          s_answer[i] = SolveLinear(s_task[i].b, s_task[i].c);
        else
          s_answer[i] = SolveQuadratic(s_task[i].a, s_task[i].b, s_task[i].c);
      }
    }
  }// else if student is average

  else { //student is good
    for (i = 0; i < s_len; i++) {
      if (s_task[i].a == 0.0)
        s_answer[i] = SolveLinear(s_task[i].b, s_task[i].c);
      else
        s_answer[i] = SolveQuadratic(s_task[i].a, s_task[i].b, s_task[i].c);
    }
  }
}

void Student::SendLetter() {
  if (!s_answer)
    return;

  letter_t letter;
  letter.tasks = s_task;
  letter.ans = s_answer;
  letter.name = s_name;

  queue_of_letters.push(letter);
}