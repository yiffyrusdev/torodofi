#include "task.hpp"
#include "functions.hpp"

using namespace std;

namespace torodofi {
namespace task {

bool compareByPriority(const SingleTask &a, const SingleTask &b) {
  return a.priority < b.priority;
}

void TaskContainer::_ParseLine(string aline, int apriority) {
  vector<string> parsed_line;
  vector<string> tags_categories;

  int del = aline.find(task_format_delimiter);

  if (del == 0) {
    _tasks.push_back(SingleTask());

    aline = aline.substr(task_format_delimiter.length());
    parsed_line = func::stringToVector(aline, task_field_delimiter);

    _tasks.back().categories = func::stringToVector(parsed_line.back(), " ");
    parsed_line.pop_back();
    _tasks.back().tags = func::stringToVector(parsed_line.back(), " ");
    parsed_line.pop_back();

    _tasks.back().expire_date = parsed_line.back();
    parsed_line.pop_back();
    _tasks.back().creation_date = parsed_line.back();
    parsed_line.pop_back();
    _tasks.back().text = parsed_line.back();
    parsed_line.pop_back();
    _tasks.back().priority = apriority;
  }
}

string TaskContainer::_ComposeTaskString(SingleTask task) {
  string result = task_format_delimiter;

  result += task.text + task_field_delimiter;
  result += task.creation_date + task_field_delimiter;
  result += task.expire_date + task_field_delimiter;
  result += func::vectorToString(task.tags) + task_field_delimiter;
  result += func::vectorToString(task.categories) + task_field_delimiter;
  return result;
}

string TaskContainer::_ComposePrioString(SingleTask task) {
  string result = task_prority_delimiter;
  result += to_string(task.priority);
  return result;
}

void TaskContainer::_SortContainer() {
  sort(_tasks.begin(), _tasks.end(), compareByPriority);
}

void TaskContainer::ReadFile(string afilename) {
  _filename = afilename;

  string line;
  size_t delim_len = task_prority_delimiter.length();
  size_t ipriority;
  int curr_priority;
  ifstream task_file(_filename);

  if (task_file.is_open()) {
    while (getline(task_file, line)) {
      ipriority = line.find(task_prority_delimiter);
      if (ipriority == 0)
        curr_priority =
            atoi(line.substr(ipriority + delim_len, ipriority + delim_len + 2)
                     .c_str());

      _ParseLine(line, curr_priority);
    }
    _SortContainer();
  } else {
    printf("No task file.md!");
  }
}

void TaskContainer::DumpToFile(string afilename) {
  if (afilename == "")
    afilename = _filename;

  int priority;

  ofstream task_file(afilename);
  if (task_file.is_open()) {
    for (size_t t = 0; t < _tasks.size(); t++) {
      if (_tasks[t].priority != priority) {
        priority = _tasks[t].priority;
        task_file << _ComposePrioString(_tasks[t]) << endl;
      }
      task_file << _ComposeTaskString(_tasks[t]) << endl;
    }
  } else {
    printf("IO ERROR!!!");
  }
}

void TaskContainer::ReadFile(char *afilename) { ReadFile(string(afilename)); }

void TaskContainer::DumpToFile(char *afilename) {
  DumpToFile(string(afilename));
}

void TaskContainer::ReRead() { ReadFile(_filename); }

vector<SingleTask> TaskContainer::getTasks() { return _tasks; }
} // namespace task
} // namespace torodofi
