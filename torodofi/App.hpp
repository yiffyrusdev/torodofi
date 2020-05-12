#pragma once

#include "Config/Config.hpp"
#include "Tasks/Task.hpp"
#include "Tasks/TaskContainer.hpp"
#include "logic.hpp"
#include "types.hpp"

namespace toro {
namespace app {

class App {
protected:
  config::Config _objConfig;
  types::config _config;
  tasks::TaskContainer _objTasks;
  std::vector<tasks::Task> _tasks;

  // Read configuration file
  void _readConfig(std::string afilename);
  // Read .md file with tasks
  void _readTasks(std::string afilename);

  // Show rofi window with active tasks list
  // return selected task
  std::string _showActiveTasks();

public:
  // Constructor
  App(std::string aconfigfilename);
  // Start Application
  void Start();
};

} // namespace app
} // namespace toro
