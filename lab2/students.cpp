#include "header.h"
#pragma warning(disable:4996)

class Student {
private:
  string s_name;
  rate_t s_rate;     //defines is student good, average or bad
  task_t* s_task;    //array of quadratic equations
  answer_t* s_answer;//array of answers on equations
  int s_len;         //amount of both equations and answers

public:
  Student(const char* name, rate_t rate) {
    s_rate = rate;
    s_name = string(name);
    s_task = NULL;
    s_answer = NULL;
    s_len = 0;
  }

  ~Student() {
    delete[] s_task;
    delete[] s_answer;
  }

  void ReadTask(const char* str) {
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

  void SolveTask() {

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

    //if average student, answer can be correct and incorrect
    else if (s_rate == AVERAGE) {
      if (rand() % 2) { //bad :(
        for (i = 0; i < s_len; i++) {
          s_answer[i].num = 1;
          s_answer[i].ans[0] = 0.0;
        }
      }
      else { //good :)

        for (i = 0; i < s_len; i++) {
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

  void PrintAnswer() {

    //if equations were not solved yet
    if (s_answer == NULL)
      return;

    int i = 0;
    for (i = 0; i < s_len; i++)
      PrintAnswers(&s_answer[i]);
  }
};

//an example of working
int main(void) {
  Student student1("Thomas", GOOD);
  Student student2("Peter", BAD);
  Student student3("Kenny", AVERAGE);

  student1.ReadTask("tasks.txt");
  student2.ReadTask("tasks.txt");
  student3.ReadTask("tasks.txt");

  student1.SolveTask();
  student2.SolveTask();
  student3.SolveTask();

  cout << "\n\nbad:" << endl;
  student1.PrintAnswer();
  cout << "\n\ngood:" << endl;
  student2.PrintAnswer();
  cout << "\n\naverage:" << endl;
  student3.PrintAnswer();

  return 0;
}