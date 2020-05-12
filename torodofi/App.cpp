#include "App.hpp"

using namespace std;

namespace toro {
namespace app {

// class App
App::App(string aconfigfilename) {
  _readConfig(aconfigfilename);
  _readTasks(_config.path.taskfile);
}

// public

void App::Start() { string out = _showActiveTasks(); }

// protected

string App::_showActiveTasks() {
  types::returnstatus status;
  string cmd;

  vector<string> high_priorities;
  vector<string> medi_priorities;
  unsigned task_priority;

  // Tasts already sorted by priority!
  for (size_t t = 0; t < _tasks.size(); t++) {
    switch (_tasks[t].getPriority()) {
    case 1:
      high_priorities.push_back(to_string(_tasks[t].getId()));
      break;
    case 2:
      medi_priorities.push_back(to_string(_tasks[t].getId()));
      break;
    }
  }

  cmd = "echo -e \"" + _objTasks.toString() + "\" | " + _config.exec.rofi + " ";
  cmd += "-u " + logic::joinString(high_priorities, ",") + " ";
  cmd += "-a " + logic::joinString(medi_priorities, ",") + " ";

  printf("%s\n", cmd.c_str());

  status = logic::execCommand(cmd);
  printf("%s\n", status.output.c_str());
  return status.output;
}

void App::_readConfig(string afilename) {
  _objConfig.readFile(afilename);
  _config = _objConfig.getConfig();
}

void App::_readTasks(string afilename) {
  _objTasks.readFile(afilename);
  _tasks = _objTasks.getTasks();
}

} // namespace app
} // namespace toro
