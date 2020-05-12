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
  string cmd = "echo -e \"" + _objTasks.toString() + "\" | ";

  cmd += _config.exec.rofi;
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
