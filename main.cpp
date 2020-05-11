#include <stdio.h>
#include <string>

#include "torodofi_lib/config.hpp"
#include "torodofi_lib/functions.hpp"
#include "torodofi_lib/interface.hpp"
#include "torodofi_lib/task.hpp"

using namespace std;

torodofi::config::ConfigParser ConfigParser;
torodofi::config::Config Config;
torodofi::task::TaskContainer TaskContainer;
torodofi::interface::Dialog Dialog;
torodofi::func::ReturnStatus ReturnStatus;

int handleTaskSelection(torodofi::func::ReturnStatus status);

int main(int argc, char *argv[]) {
  int statuscode = 0;
  bool infiniteShow = true;

  int selectedtaskid;

  ConfigParser.ReadFile("config");
  TaskContainer.ReadFile(ConfigParser.getPathset().notefile);

  Dialog.Configure(ConfigParser.getConfig());
  while (infiniteShow) {
    ReturnStatus = Dialog.ShowMain(TaskContainer.getTasks());
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
      selectedtaskid = handleTaskSelection(ReturnStatus);
      if (selectedtaskid >= 0)
        Dialog.ShowTask(TaskContainer.getTasks()[selectedtaskid]);
      else
        infiniteShow = false;
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

int handleTaskSelection(torodofi::func::ReturnStatus status) {
  string chose(status.content);
  string chose_back(torodofi::interface::menu_back);

  size_t idbeg = status.content.find("id:") + 3;
  int selectedid = atoi(status.content.substr(idbeg).c_str());
  return selectedid;
}
