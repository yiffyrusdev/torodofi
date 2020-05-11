#pragma once

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Task.hpp"

namespace toro {
namespace tasks {

const std::string priority_start_point = "## ";

class TaskContainer {
protected:
  std::vector<Task> _tasks;
  std::string _filename;

  // Sort containered Tasks by priority;
  void _sort_priority();

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
  // Dump task to a file back
  void Dump(std::string afilename = "");

  std::vector<Task> getTasks();
};

} // namespace tasks
} // namespace toro
