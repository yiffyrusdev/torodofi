#include <stdio.h>
#include <string>

#include "torodofi/Tasks/TaskContainer.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  toro::tasks::TaskContainer tasks("example.md");
  printf("%s", tasks.getTasks()[0].getTask().text.c_str());
  return 0;
}
