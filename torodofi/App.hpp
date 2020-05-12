#pragma once

#include <functional>

#include "Config/Config.hpp"
#include "Tasks/Task.hpp"
#include "Tasks/TaskContainer.hpp"
#include "logic.hpp"
#include "types.hpp"

namespace toro {
namespace app {

const std::string rofi_options_delimiter = tasks::string_repr_delimiter;

const std::string menu_back = "< Back";

const std::vector<std::string> any_menu_actions = {menu_back};

const std::vector<std::string> one_task_actions = {"0 Mark as done", "1 Edit"};

const std::vector<std::string> edit_task_options = {"0 Text", "1 Deadline",
                                                    "2 Tags", "3 Categories"};

class App {
protected:
  config::Config _objConfig;
  tasks::TaskContainer _objTasks;

  std::string active_tasks_caption;

  // Read configuration file
  void _readConfig(std::string afilename);
  // Read .md file with tasks
  void _readTasks(std::string afilename);

  // Compose cmdline for task-base menus
  std::string _task_based_menu(tasks::Task atask,
                               std::vector<std::string> add_menu);
  std::string _caption_based_menu(std::string acaption, std::string add_menu,
                                  std::string aprompt);
  // Show rofi window with active tasks list
  // return selected fiels string
  types::returnstatus _showActiveTasks();
  // Show rofi window with one Task information
  // return selected action string
  types::returnstatus _showOneTask(unsigned aid);
  // Edit selected by id task
  void _editTask(unsigned aid);

public:
  // Constructor
  App(std::string aconfigfilename);
  // Start Application
  void Start();
};

} // namespace app
} // namespace toro
