#include "header.h"

Teacher::Teacher(const char* str): Human(str) {}

Teacher::~Teacher() {
  while (queue_of_letters.size() != 0)
    queue_of_letters.pop();
}

void Teacher::SolveTaskCorrectly() {
  if (!tasks) //if there are now tasks yet
    return;
  for (int i = 0; i < len; i++)
    tasks[i].SolveTaskCorrectly();
}

void Teacher::ReceiveLetter(Letter letter) {
  queue_of_letters.push(letter);
}

void Teacher::CheckLetters() {
  int size = (int)queue_of_letters.size();
  if (size == 0) //students did not send ans to teacher
    return;

  int i;
  Letter letter;
  Mark mark;

  while (!queue_of_letters.empty()) {
    letter = queue_of_letters.front(); //get from queue first letter
    queue_of_letters.pop(); //remove it from queue

    mark.name = letter.name;
    mark.score = 0;

    for (i = 0; i < len; i++) {

      //if (letter.tasks.ans[i].numOfAns == tasks.ans[i].numOfAns) {
      if ( letter.tasks[i].numOfAns == tasks[i].numOfAns) {
        if (tasks[i].numOfAns == 0 || tasks[i].numOfAns == INF)
          mark.score++;
        else if (tasks[i].numOfAns == 1 && letter.tasks[i].ans[0] == tasks[i].ans[0])
          mark.score++;
        else if (tasks[i].numOfAns == 2 && \
          letter.tasks[i].ans[0] == tasks[i].ans[0]\
          && letter.tasks[i].ans[1] == tasks[i].ans[1])
          mark.score++;
      }
    }
    table.push_back(mark);
  }

}

void Teacher::PublishTable() {

  if (table.size() == 0) //table is empty
    return;

  list <Mark>::iterator it;
  cout << "Results (max: " << len << "):" <<endl;
  for (it = table.begin(); it != table.end(); ++it) {
    cout << it->name << " - " << it->score << endl;
  }
}