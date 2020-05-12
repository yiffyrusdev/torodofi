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

void App::Start() {
  string choice;
  unsigned choice_id;
  types::returnstatus status;

  bool showactive = true;
  bool showtask = false;

  while (showactive) {
    status = _showActiveTasks();
    choice = status.output;
    choice = choice.substr(0, choice.length() - 1); // remove \n symbol
    if (choice == menu_back) {
      showactive = false;
    } else {
      choice_id = atoi(logic::splitString(choice)[0].c_str());
      showtask = true;
    }

    while (showtask) {
      status = _showOneTask(choice_id);
      choice = status.output;
      choice = choice.substr(0, choice.length() - 1); // remove \n symbol
      if (choice == menu_back) {
        showtask = false;
      } else {
        showtask = true;
      }
    }
  }
}

// protected

types::returnstatus App::_showActiveTasks() {
  size_t prio_offset = any_menu_actions.size();
  types::returnstatus status;
  string cmd;
  vector<string> high_priorities;
  vector<string> medi_priorities;
  unsigned task_priority;

  // Tasts already sorted by priority!
  for (size_t t = 0; t < _tasks.size(); t++) {
    switch (_tasks[t].getPriority()) {
    case 1:
      high_priorities.push_back(to_string(_tasks[t].getId() + prio_offset));
      break;
    case 2:
      medi_priorities.push_back(to_string(_tasks[t].getId() + prio_offset));
      break;
    }
  }

  cmd = "echo -e \"";
  cmd += logic::joinString(any_menu_actions, rofi_options_delimiter) +
         rofi_options_delimiter;
  cmd += _objTasks.toString() + "\" | ";
  cmd += _config.exec.rofi + " ";
  cmd += "-dmenu -p \"Active\" ";
  cmd += "-u " + logic::joinString(high_priorities, ",") + " ";
  cmd += "-a " + logic::joinString(medi_priorities, ",") + " ";
  cmd += "-mesg " + active_tasks_caption;
  status = logic::execCommand(cmd);

  return status;
}

types::returnstatus App::_showOneTask(unsigned aid) {
  types::returnstatus status;
  vector<string> caption;
  string cmd;

  caption = {
      _tasks[aid].getText() + " " + _tasks[aid].getCreation().toString(),
      "Deadline: " + _tasks[aid].getExpire().toString(),
      "Tags: " + logic::joinString(_tasks[aid].getTags(),
                                   tasks::task_field_inner_delimiter),
      "Categories: " + logic::joinString(_tasks[aid].getCategories(),
                                         tasks::task_field_inner_delimiter),
  };

  cmd += "echo -e \"";
  cmd += logic::joinString(any_menu_actions, rofi_options_delimiter) +
         rofi_options_delimiter;
  cmd += logic::joinString(one_task_actions, rofi_options_delimiter) +
         rofi_options_delimiter;

  cmd += "\" | ";
  cmd += _config.exec.rofi + " ";
  cmd += "-dmenu -p \"Task\" ";
  cmd += "-mesg \"" + logic::joinString(caption, "\n") + "\"";

  status = logic::execCommand(cmd);

  return status;
}

void App::_readConfig(string afilename) {
  _objConfig.readFile(afilename);
  _config = _objConfig.getConfig();

  active_tasks_caption = "\"Have a nice day!\n";
  active_tasks_caption += _config.keys.kb_new_task + "to add new task\n";
  active_tasks_caption += _config.keys.kb_active_done + "to view done tasks\n";
  active_tasks_caption += _config.keys.kb_task_agenda + "to view agenda";
  active_tasks_caption += "\"";
}

void App::_readTasks(string afilename) {
  _objTasks.readFile(afilename);
  _tasks = _objTasks.getTasks();
}

} // namespace app
} // namespace toro
