#include "torodofi_config.h"
#include "torodofi_task.h"

#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  Config config;
  TaskContainer tasks;

  config.ReadFile("config");
  tasks.ReadFile(config.getPathset().notefile);
  return 0;
}
