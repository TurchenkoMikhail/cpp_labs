#include "header.h"

Human::Human(const char* str) {
  name = string(str);
  task = NULL;
  answer = NULL;
  len = 0;
}

Human::~Human() {
  if (task) {
    delete[] task;
    task = NULL;
  }
  if (answer) {
    delete[] answer;
    answer = NULL;
  }
}

void Human::ReadTask(const char* str) {
  FILE* filename = fopen(str, "r");
  if (!filename)
    return;

  int i;
  char c;

  while (!feof(filename)) {
    fscanf(filename, "%c", &c);
    if (c == '\n')
      len++;
  }
  len--;
  task = new task_t[len];

  fseek(filename, 0, SEEK_SET);

  for (i = 0; i < len; i++)
    fscanf(filename, "%lf%lf%lf", &task[i].a, &task[i].b, &task[i].c);

  fclose(filename);
}

//right answers
void Human::SolveTask() {

  if (!task) //if there are now tasks yet
    return;

  answer = new answer_t[len];
  int i;

  for (i = 0; i < len; i++) {
    if (task[i].a == 0.0)
      answer[i] = SolveLinear(task[i].b, task[i].c);
    else
      answer[i] = SolveQuadratic(task[i].a, task[i].b, task[i].c);
  }
}