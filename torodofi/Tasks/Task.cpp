#include "Task.hpp"

using namespace std;

namespace toro {
namespace tasks {

Task::Task() {}

Task::Task(string atask, unsigned id, unsigned priority) {
  vector<string> parsed_task = _validate_and_pass(atask);
  // task fields
  types::date creation_date;
  types::date expire_date;
  vector<string> tags;
  vector<string> categories;
  string text;
  vector<string> vector_text;

  creation_date = types::date(parsed_task[0]);
  expire_date = types::date(parsed_task[1]);
  tags = logic::splitString(parsed_task[2], task_field_inner_delimiter);
  categories = logic::splitString(parsed_task[3], task_field_inner_delimiter);
  vector_text = vector<string>(parsed_task.begin() + 4, parsed_task.end());
  text = logic::joinString(vector_text);

  _task.creation_date = creation_date;
  _task.expire_date = expire_date;
  _task.tags = tags;
  _task.categories = categories;
  _task.text = text;
}

vector<string> Task::_validate_and_pass(string atask) {
  short start_pos = atask.find(task_start_point);
  vector<string> parsed_task;

  if (start_pos >= 0) {
    start_pos += task_start_point.length();
    parsed_task = logic::splitString(atask.substr(start_pos));
    if (parsed_task.size() >= 5) {
      return parsed_task;
    } else {
      printf("string atask: %s", atask.c_str());
      throw std::invalid_argument("Task has less then 5 fields");
    }
  } else {
    printf("string atask: %s", atask.c_str());
    throw std::invalid_argument("Task Start Point was not found");
  }
}

types::task Task::getTask() { return _task; }

} // namespace tasks
} // namespace toro
