#include "TaskContainer.hpp"

using namespace std;

namespace toro {
namespace tasks {

void TaskContainer::_sort_priority() {
  sort(_tasks.begin(), _tasks.end(), cmp_prioroty);
}

// class TaskContainer
TaskContainer::TaskContainer() {}
TaskContainer::TaskContainer(string afilename) {
  size_t pri_del_len = priority_start_point.length();
  string line;
  unsigned priority;
  ifstream file(afilename);

  if (file.is_open()) {
    // Read file: priorities and tasks
    while (getline(file, line)) {
      if (line.find(priority_start_point) == 0) {
        priority = atoi(line.substr(pri_del_len, pri_del_len + 2).c_str());
      } else {
        if (line.find(task_start_point) >= 0) {
          _tasks.push_back(Task(line, priority));
        }
      }
    }
    // Sort read tasks by priority
    _sort_priority();
    // Give ID to sorted tasks
    for (size_t i = 0; i < _tasks.size(); i++) {
      _tasks[i].setId(i);
    }
  } else {
    printf("string afilename: %s\n", afilename.c_str());
    throw std::invalid_argument("File could not be opened");
  }
}

vector<Task> TaskContainer::getTasks() { return _tasks; }

} // namespace tasks
} // namespace toro
