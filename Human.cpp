#include "header.h"

Human::Human(string str) {
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
    fscanf_s(filename, "%c", &c, 1);
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