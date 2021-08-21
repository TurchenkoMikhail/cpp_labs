#include "header.h"

//detecting possible memory leaks
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

//an example of working
int main(void) {
  GoodStudent student1("Thomas");
  AverageStudent student2("Harry");
  BadStudent student3("Ben");

  Teacher teacher("Mr. Brown");

  student1.ReadTask("tasks.txt");
  student1.SolveTask();
  student1.SendLetter(teacher);

  student2.ReadTask("tasks.txt");
  student2.SolveTask();
  student2.SendLetter(teacher);

  student3.ReadTask("tasks.txt");
  student3.SolveTask();
  student3.SendLetter(teacher);

  teacher.ReadTask("tasks.txt");
  teacher.SolveTaskCorrectly();
  teacher.CheckLetters();
  teacher.PublishTable();

  _CrtDumpMemoryLeaks();
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
  return 0;
}
