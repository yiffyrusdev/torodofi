#include "Task.hpp"

using namespace std;

namespace toro {
namespace tasks {

// functions

bool cmp_prioroty(Task &a, Task &b) {
  bool alessb{false};
  if (a.getPriority() == b.getPriority()) {
    alessb = a.getExpire() < b.getExpire();
  } else {
    alessb = a.getPriority() < b.getPriority();
  }

  return alessb;
}

// class Task
Task::Task() : _task{} {}
Task::Task(string atext, types::date expire, vector<string> atags,
           vector<string> acategories, unsigned apriority)
    : _task{} {
  _task.text = atext;
  _task.expire_date = expire;
  _task.tags = atags;
  _task.categories = acategories;
  _task.creation_date = types::date(); // empty constructs today
  _task.priority = apriority;
  _task.is_active = true;
}

Task::Task(string ataskline, unsigned apriority) : _task{} {
  vector<string> parsed_task{_validate_and_pass(ataskline)};
  // task fields
  types::date creation_date(parsed_task[0]);
  types::date expire_date(parsed_task[1]);
  vector<string> tags{
      logic::splitString(parsed_task[2], task_field_inner_delimiter)};
  vector<string> categories{
      logic::splitString(parsed_task[3], task_field_inner_delimiter)};
  vector<string> vector_text{
      vector<string>(parsed_task.begin() + 4, parsed_task.end() - 1)};
  string text{logic::joinString(vector_text)};
  bool is_active{(parsed_task[parsed_task.size() - 1] == "1") ? true : false};

  setPriority(apriority);
  _task.creation_date = creation_date;
  setExpire(expire_date);
  setTags(tags);
  setCategories(categories);
  setActive(is_active);
  setText(text);
} // namespace tasks

vector<string> Task::_validate_and_pass(string atask) {
  size_t active_start_pos{atask.find(task_start_point_active)};
  size_t done_start_pos{atask.find(task_start_point_done)};
  size_t start_pos{string::npos};
  string start_point, is_active;
  vector<string> parsed_task;

  if (active_start_pos != string::npos) {
    start_pos = active_start_pos;
    start_point = task_start_point_active;
    is_active = "1";
  } else if (done_start_pos != string::npos) {
    start_pos = done_start_pos;
    start_point = task_start_point_done;
    is_active = "0";
  }

  if (start_pos != string::npos) {
    start_pos += start_point.length();
    parsed_task = logic::splitString(atask.substr(start_pos));
    parsed_task.push_back(is_active);
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

string Task::toFileString() {
  string start_point;
  vector<string> vectorized{
      _task.creation_date.c_str(), _task.expire_date.c_str(),
      logic::joinString(_task.tags, task_field_inner_delimiter),
      logic::joinString(_task.categories, task_field_inner_delimiter),
      _task.text};

  start_point =
      (_task.is_active) ? task_start_point_active : task_start_point_done;
  return start_point + logic::joinString(vectorized, task_field_delimiter);
}

string Task::toString(string delimiter) {
  string result = to_string(_task.id + 1) + delimiter;
  if (_task.is_active) {
    if (_task.expire_date < _task.expire_date.today()) {
      result += "[EXPIRED] ";
    } else if (_task.expire_date == _task.expire_date.today()) {
      result += "[DEADLINE] ";
    }
  }
  result += _task.text + delimiter;
  result += _task.expire_date.toString() + delimiter;
  result += logic::joinString(_task.tags, ",") + delimiter;
  result += logic::joinString(_task.categories, ",") + delimiter;

  return result;
} // namespace tasks

// getters
types::task Task::getTask() { return _task; }
unsigned Task::getPriority() { return _task.priority; }
unsigned Task::getId() { return _task.id; }
bool Task::getActive() { return _task.is_active; }
std::string Task::getText() { return _task.text; }
types::date Task::getCreation() { return _task.creation_date; }
types::date Task::getExpire() { return _task.expire_date; }
std::vector<std::string> Task::getTags() { return _task.tags; }
std::vector<std::string> Task::getCategories() { return _task.categories; }
// setters
void Task::setActive(bool is_active) { _task.is_active = is_active; }
void Task::_setId(unsigned int aid) { _task.id = aid; }
void Task::setPriority(unsigned apriority) { _task.priority = apriority; }
void Task::setExpire(types::date adate) {
  if (_task.creation_date <= adate) {
    _task.expire_date = adate;
  }
}
void Task::setTags(std::vector<std::string> atags) {
  if (atags.size() > 0) {
    _task.tags = atags;
  } else {
    _task.tags = vector<string>() = {empty_tag};
  }
}
void Task::setCategories(std::vector<std::string> acategories) {
  if (acategories.size() > 0) {
    _task.categories = acategories;
  } else {
    _task.categories = vector<string>() = {empty_category};
  }
}
void Task::setText(std::string atext) { _task.text = atext; }

} // namespace tasks
} // namespace toro
