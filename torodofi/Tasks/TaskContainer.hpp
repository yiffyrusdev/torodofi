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
const std::string string_repr_delimiter = "\n";

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
  // Read tasks file
  void readFile(std::string afilename);
  // Dump task to a file back
  void Dump(std::string afilename = "");
  // Repr task container as formatted string with delimiter
  std::string toString(std::string delimiter = string_repr_delimiter);

  std::vector<Task> getTasks();
  Task *getTask(size_t index);
};

} // namespace tasks
} // namespace toro
