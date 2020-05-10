#include "torodofi_lib/config.hpp"
#include "torodofi_lib/task.hpp"

#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  torodofi_lib::Config config;
  torodofi_lib::TaskContainer tasks;

  config.ReadFile("config");
  tasks.ReadFile(config.getPathset().notefile);
  return 0;
}
