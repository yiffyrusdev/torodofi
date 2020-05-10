#include "torodofi_lib/config.cpp"
#include "torodofi_lib/functions.hpp"
#include "torodofi_lib/interface.cpp"
#include "torodofi_lib/task.cpp"

#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  int statuscode = 0;
  bool infiniteShow = true;

  torodofi_lib::config::ConfigParser ConfigParser;
  torodofi_lib::config::Config Config;
  torodofi_lib::task::TaskContainer TaskContainer;
  torodofi_lib::interface::Dialog Dialog;

  torodofi_lib::func::ReturnStatus ReturnStatus;

  ConfigParser.ReadFile("config");
  TaskContainer.ReadFile(ConfigParser.getPathset().notefile);

  Dialog.Configure(ConfigParser.getConfig());
  while (infiniteShow) {
    ReturnStatus = Dialog.ShowMain(TaskContainer.getTasks());
    printf("%d\n", ReturnStatus.status);
    switch (ReturnStatus.status) {
    case 256: // window closed
      infiniteShow = false;
      break;
    case 10: // custom-keycode-1 -- add new task
      break;
    case 11: // custom-keycode-2 -- done/active
      break;
    case 12: // custom-keycode-3 -- agenda
      break;
    case 0: // item selected
      break;
    default:
      statuscode = 127;
      infiniteShow = false;
      break;
    }
  }
  if (statuscode == 0) { // final options before program stops
    TaskContainer.DumpToFile();
  }
  return statuscode;
}
