#pragma once

#include "Task.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace toro {
namespace tasks {

const std::string priority_start_point = "## ";

class TaskContainer {
protected:
  std::vector<Task> _tasks;
  std::string _filename;

public:
  TaskContainer();
  // Reads collection of tasks from .md file
  // .md have to be declared as way:
  // ## 1
  // * .... task
  // * .... task
  // ## 2
  // ......
  // ## (x) means (x) priority of listed tasks
  TaskContainer(std::string afilename);

  std::vector<Task> getTasks();
};

} // namespace tasks
} // namespace toro
