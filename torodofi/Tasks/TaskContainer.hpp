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
  std::vector<std::string> _categories;
  std::vector<std::string> _tags;
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
  // Add new task
  void addTask(std::string atext, types::date expire,
               std::vector<std::string> atags,
               std::vector<std::string> acategories, unsigned apriority);
  // Add new category
  void addCategory(std::string acat);
  void addCategory(std::vector<std::string> acats);
  // Add new tag
  void addTag(std::string atag);
  void addTag(std::vector<std::string> atags);
  // Repr task container as formatted string with delimiter
  std::string toString(std::string delimiter = string_repr_delimiter);

  // getters
  std::vector<Task> getTasks();
  std::vector<std::string> getTags();
  std::vector<std::string> getCategories();
  Task *getTask(size_t index);
};

} // namespace tasks
} // namespace toro
