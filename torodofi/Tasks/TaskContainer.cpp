#include "TaskContainer.hpp"

using namespace std;

namespace toro {
namespace tasks {

// class TaskContainer
TaskContainer::TaskContainer() {}
TaskContainer::TaskContainer(string afilename) {
  size_t pri_del_len = priority_start_point.length();
  string line;
  unsigned id, priority;
  ifstream file(afilename);

  if (file.is_open()) {
    while (getline(file, line)) {
      if (line.find(priority_start_point) == 0) {
        priority = atoi(line.substr(pri_del_len, pri_del_len + 2).c_str());
      } else {
        if (line.find(task_start_point) >= 0) {
          _tasks.push_back(Task(line, id, priority));
          id++;
        }
      }
    }
  } else {
    printf("string afilename: %s\n", afilename.c_str());
    throw std::invalid_argument("File could not be opened");
  }
}

vector<Task> TaskContainer::getTasks() { return _tasks; }

} // namespace tasks
} // namespace toro
