#include <stdio.h>
#include <string>

#include "torodofi/Tasks/TaskContainer.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  toro::tasks::TaskContainer tasks("example.md");
  toro::types::date new_date;

  printf("%s\n", tasks.getTasks()[0].getTask().text.c_str());
  tasks.Dump();

  new_date = "2020-05-15";
  printf("%s\n", tasks.getTasks()[0].getTask().creation_date.c_str());
  printf("%s\n\n", tasks.getTasks()[0].getTask().expire_date.c_str());
  tasks.getTasks()[0].setExpire(new_date);
  printf("%s\n", tasks.getTasks()[0].getTask().expire_date.c_str());
  return 0;
}
