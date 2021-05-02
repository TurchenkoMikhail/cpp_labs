#include "header.h"
#define _CRT_SECURE_NO_WARNINGS

Human::Human(const char* str) {
  name = string(str);
  tasks = NULL;
  len = 0;
}

Human::~Human() {
  if (tasks) {
    delete[] tasks;
    tasks = NULL;
  }
}

void Human::ReadTask(const char* str) {
  FILE* filename = NULL;
  fopen_s(&filename, str, "r");
  if (!filename)
    return;

  int i;
  char c;

  while (!feof(filename)) {
    fscanf_s(filename, "%c", &c);
    if (c == '\n')
      len++;
  }
  len--;
  tasks = new Equation[len];

  fseek(filename, 0, SEEK_SET);

  for (i = 0; i < len; i++)
    fscanf_s(filename, "%lf%lf%lf", &tasks[i].a, &tasks[i].b, &tasks[i].c);

  fclose(filename);
}

//right answers
void Human::SolveTask() {

  if (!tasks) //if there are now tasks yet
    return;

  int i;

  for (i = 0; i < len; i++) {
    if (tasks[i].a == 0.0)
      tasks[i].SolveLinear();
    else
      tasks[i].SolveQuadratic();
  }
}