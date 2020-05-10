#include <stdio.h>
#include <string>

#include "torodofi_lib/config.hpp"
#include "torodofi_lib/functions.hpp"
#include "torodofi_lib/interface.hpp"
#include "torodofi_lib/task.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  int statuscode = 0;
  bool infiniteShow = true;

  torodofi::config::ConfigParser ConfigParser;
  torodofi::config::Config Config;
  torodofi::task::TaskContainer TaskContainer;
  torodofi::interface::Dialog Dialog;

  torodofi::func::ReturnStatus ReturnStatus;

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
