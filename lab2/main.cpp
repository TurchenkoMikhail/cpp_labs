#include "header.h"

//an example of working
int main(void) {
  queue <Letter> queue_of_letters;
  list <Mark> table;

  GoodStudent student1("Thomas");
  AverageStudent student2("Harry");
  BadStudent student3("Ben");

  Teacher teacher("Mr. Brown");

  student1.ReadTask("tasks.txt");
  student1.SolveTask();
  student1.SendLetter(&queue_of_letters);

  student2.ReadTask("tasks.txt");
  student2.SolveTask();
  student2.SendLetter(&queue_of_letters);

  student3.ReadTask("tasks.txt");
  student3.SolveTask();
  student3.SendLetter(&queue_of_letters);

  teacher.ReadTask("tasks.txt");
  teacher.SolveTask();
  teacher.CheckLetterFromQueue(&queue_of_letters, &table);
  teacher.PublishTable(&table);

  return 0;
}
