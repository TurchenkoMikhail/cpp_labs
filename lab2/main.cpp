#include "header.h"

queue <letter_t> queue_of_letters;
list <mark_t> table;

//an example of working
int main(void) {
  Student student1("Thomas", GOOD);
  Student student2("Harry", AVERAGE);
  Student student3("Ben", BAD);

  Teacher teacher;

  student1.ReadTask("tasks.txt");
  student1.SolveTask();
  student1.SendLetter();

  student2.ReadTask("tasks.txt");
  student2.SolveTask();
  student2.SendLetter();

  student3.ReadTask("tasks.txt");
  student3.SolveTask();
  student3.SendLetter();

  teacher.GetTask("tasks.txt");
  teacher.GetRightAnswers();
  teacher.CheckLetterFromQueue();
  teacher.PublishTable();

  return 0;
}
