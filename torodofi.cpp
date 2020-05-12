#include <stdio.h>
#include <string>

#include "torodofi/Config/Config.hpp"
#include "torodofi/Tasks/TaskContainer.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  toro::tasks::TaskContainer tasks;
  toro::config::Config configs;
  toro::types::date new_date;

  configs.readFile("example.cfg");
  tasks.readFile(configs.getConfig().path.taskfile);

  printf("%s\n-TASKCHECK-\n", tasks.getTasks()[0].getTask().text.c_str());
  tasks.Dump();

  new_date = "2020-05-15";
  printf("%s\n", tasks.getTasks()[0].getTask().creation_date.c_str());
  printf("%s\n\n", tasks.getTasks()[0].getTask().expire_date.c_str());
  tasks.getTasks()[0].setExpire(new_date);
  printf("%s\n---\n", tasks.getTasks()[0].getTask().expire_date.c_str());

  printf("%s\n---\n", tasks.toString().c_str());

  return 0;
}
