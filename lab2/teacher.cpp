#include "header.h"

Teacher::Teacher(void) {
  t_task = NULL;
  t_rightanswers = NULL;
  t_len = 0;
}
Teacher::~Teacher() {
  if (t_task)
    delete[] t_task;
  if (t_rightanswers)
    delete[] t_rightanswers;

}

void Teacher::GetTask(const char* str) {
  FILE* filename = fopen(str, "r");
  if (!filename)
    return;

  int i;
  char c;

  while (!feof(filename)) {
    fscanf(filename, "%c", &c);
    if (c == '\n')
      t_len++;
  }
  t_len--;
  t_task = new task_t[t_len];

  fseek(filename, 0, SEEK_SET);

  for (i = 0; i < t_len; i++)
    fscanf(filename, "%lf%lf%lf", &t_task[i].a, &t_task[i].b, &t_task[i].c);

  fclose(filename);
}
void Teacher::GetRightAnswers() {

  if (!t_task) //if there are now tasks yet
    return;

  t_rightanswers = new answer_t[t_len];
  int i;

  for (i = 0; i < t_len; i++) {
    if (t_task[i].a == 0.0)
      t_rightanswers[i] = SolveLinear(t_task[i].b, t_task[i].c);
    else
      t_rightanswers[i] = SolveQuadratic(t_task[i].a, t_task[i].b, t_task[i].c);
  }

}

void Teacher::CheckLetterFromQueue() {

  int size = queue_of_letters.size();
  if (size == 0) //students did not send answers to teacher
    return;

  int i;
  letter_t letter;
  mark_t mark;

  while (!queue_of_letters.empty()) {
    letter = queue_of_letters.front(); //get from queue first letter
    queue_of_letters.pop(); //remove it from queue
    mark_t mark;

    mark.name = letter.name;
    mark.score = 0;

    for (i = 0; i < t_len; i++) {

      if (letter.ans[i].num == t_rightanswers[i].num) {

        if (t_rightanswers[i].num == 0 || t_rightanswers[i].num == INF)
          mark.score++;
        else if (t_rightanswers[i].num == 1 && letter.ans[i].ans[0] == t_rightanswers[i].ans[0])
          mark.score++;
        else if (t_rightanswers[i].num == 2 && \
          letter.ans[i].ans[0] == t_rightanswers[i].ans[0]\
          && letter.ans[i].ans[1] == t_rightanswers[i].ans[1])
          mark.score++;
      }
    }
    table.push_back(mark);
  }

}

void Teacher::PublishTable() {

  if (table.size() == 0) //table is empty
    return;

  list <mark_t> ::iterator it;
  cout << "Results (max:" << t_len << "):" <<endl;
  for (it = table.begin(); it != table.end(); it++) {
    cout << it->name << " - " << it->score << endl;
  }
}