#include "header.h"

queue <letter_t> queue_of_letters;
list <mark_t> table;

//an example of working
int main(void) {
  GoodStudent student1("Thomas");
  AverageStudent student2("Harry");
  BadStudent student3("Ben");

  Teacher teacher("Mr. Brown");

  student1.ReadTask("tasks.txt");
  student1.SolveTask();
  student1.SendLetter();

  student2.ReadTask("tasks.txt");
  student2.SolveTask();
  student2.SendLetter();

  student3.ReadTask("tasks.txt");
  student3.SolveTask();
  student3.SendLetter();

  teacher.ReadTask("tasks.txt");
  teacher.SolveTask();
  teacher.CheckLetterFromQueue();
  teacher.PublishTable();

  return 0;
}
