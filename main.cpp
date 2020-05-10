#include "torodofi_lib/config.cpp"
#include "torodofi_lib/interface.cpp"
#include "torodofi_lib/task.cpp"

#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  torodofi_lib::config::ConfigParser ConfigParser;
  torodofi_lib::config::Config Config;
  torodofi_lib::task::TaskContainer TaskContainer;
  torodofi_lib::interface::Dialog Dialog;

  ConfigParser.ReadFile("config");
  TaskContainer.ReadFile(ConfigParser.getPathset().notefile);

  Dialog.Configure(ConfigParser.getConfig());
  Dialog.ShowMain();
  // TaskContainer.DumpToFile();
  return 0;
}
