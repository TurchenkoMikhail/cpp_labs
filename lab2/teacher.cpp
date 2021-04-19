#include "header.h"

extern queue <letter_t> queue_of_letters;
extern list <mark_t> table;

Teacher::Teacher(const char* str)
  :Human(str)
{}

Teacher::~Teacher() {
  if (task) {
    delete[] task;
    task = NULL;
  }
  if (answer) {
    delete[] answer;
    answer = NULL;
  }
}

void Teacher::CheckLetterFromQueue() {

  int size = queue_of_letters.size();
  if (size == 0) //students did not send answer to teacher
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

    for (i = 0; i < len; i++) {

      if (letter.ans[i].num == answer[i].num) {

        if (answer[i].num == 0 || answer[i].num == INF)
          mark.score++;
        else if (answer[i].num == 1 && letter.ans[i].ans[0] == answer[i].ans[0])
          mark.score++;
        else if (answer[i].num == 2 && \
          letter.ans[i].ans[0] == answer[i].ans[0]\
          && letter.ans[i].ans[1] == answer[i].ans[1])
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
  cout << "Results (max: " << len << "):" <<endl;
  for (it = table.begin(); it != table.end(); it++) {
    cout << it->name << " - " << it->score << endl;
  }
}