#include "TaskContainer.hpp"

using namespace std;

namespace toro {
namespace tasks {

// class TaskContainer
TaskContainer::TaskContainer() {
  _tags = {no_tag};
  _categories = {no_category};
}
TaskContainer::TaskContainer(string afilename) {
  _tags = {no_tag};
  _categories = {no_category};

  readFile(afilename);
}

void TaskContainer::Dump(std::string afilename) {
  if (afilename == "") {
    afilename = _filename;
  }
  unsigned priority;
  Task cmptask;
  vector<vector<Task> *> tasks;
  vector<string> h1_captions;
  ofstream file(afilename);

  _sort_priority();
  tasks = {&_tasks_active, &_tasks_done};
  h1_captions = {"# Active Tasks", "# Done Tasks"};

  if (file.is_open()) {
    for (size_t v = 0; v < tasks.size(); v++) {
      file << endl << h1_captions[v];
      priority = 0;
      for (size_t t = 0; t < (*tasks[v]).size(); t++) {
        cmptask = (*tasks[v])[t];
        if (cmptask.getTask().priority != priority) {
          priority = cmptask.getTask().priority;
          file << endl << priority_start_point + to_string(priority) << endl;
        }
        file << cmptask.toFileString() << endl;
      }
    }
  } else {
    printf("tasks::TaskContainer: string afilename: %s\n", afilename.c_str());
    throw std::runtime_error("Bad IO: could not create file");
  }
}

void TaskContainer::readFile(string afilename) {
  size_t pri_del_len = priority_start_point.length();
  string line;
  unsigned priority;
  vector<string> tmp;
  ifstream file(afilename);

  if (file.is_open()) {
    // Read file: priorities and tasks
    while (getline(file, line)) {
      if (line.length() > 1) {
        if (line.find(priority_start_point) == 0) {
          priority = atoi(line.substr(pri_del_len, pri_del_len + 2).c_str());
        } else if ((int)line.find(task_start_point_active) >= 0 ||
                   (int)line.find(task_start_point_done) >= 0) {
          addTask(Task(line, priority));
        }
      }
    }
    // If read was successfull, then we can store afilename
    _filename = afilename;
    // Sort read tasks by priority
    _sort_priority();
    // Aggregate all tags and categories
    for (size_t t = 0; t < _tasks.size(); t++) {
      addTag(_tasks[t].getTags());
      addCategory(_tasks[t].getCategories());
    }
  } // namespace tasks
  else {
    printf("tasks::TaskContainer: string afilename: %s\n", afilename.c_str());
    throw std::invalid_argument("File could not be opened");
  }
} // namespace toro

void TaskContainer::addTask(string atext, types::date expire,
                            vector<string> atags, vector<string> acategories,
                            unsigned apriority) {
  Task new_task(atext, expire, atags, acategories, apriority);
  addTask(new_task);
}

void TaskContainer::addTask(Task atask) {
  _tasks.push_back(atask);
  if (atask.getActive()) { // got Active task
    _tasks_active.push_back(atask);
  } else { // got Done task
    _tasks_done.push_back(atask);
  }
  _sort_priority();
}

void TaskContainer::delTask(size_t aid, bool is_active) {
  vector<Task> *tasks = (is_active) ? &_tasks_active : &_tasks_done;

  for (size_t i = 0; i < (*tasks).size(); i++) {
    if ((*tasks)[i].getId() == aid) {
      (*tasks).erase((*tasks).begin() + i);
    }
  }
}

void TaskContainer::addCategory(string acat) {
  if (find(_categories.begin(), _categories.end(), acat) == _categories.end()) {
    _categories.push_back(acat);
  }
}

void TaskContainer::addCategory(vector<string> acats) {
  if (acats.size() > 0) {
    for (size_t i = 0; i < acats.size(); i++) {
      if (acats[i] != empty_category) {
        addCategory(acats[i]);
      }
    }
  }
}

void TaskContainer::addTag(string atag) {
  if (find(_tags.begin(), _tags.end(), atag) == _tags.end()) {
    _tags.push_back(atag);
  }
}

void TaskContainer::addTag(vector<string> atags) {
  if (atags.size() > 0) {
    for (size_t i = 0; i < atags.size(); i++) {
      if (atags[i] != empty_tag) {
        addTag(atags[i]);
      }
    }
  }
}

string TaskContainer::toString(bool is_active, string delimiter) {
  vector<Task> *tasks = (is_active) ? &_tasks_active : &_tasks_done;
  string result;

  if ((*tasks).size() > 0) {
    for (size_t t = 0; t < (*tasks).size() - 1; t++) {
      result += (*tasks)[t].toString() + delimiter;
    }
    result += (*tasks)[(*tasks).size() - 1].toString();
    result = logic::linuxColumns(result);
  } else {
    result = "";
  }

  return result;
}

void TaskContainer::sortByPriority() { _sort_priority(); }

void TaskContainer::refreshActiveDone() {
  _tasks = _tasks_active;
  _tasks.insert(_tasks.end(), _tasks_done.begin(), _tasks_done.end());
  _tasks_active.clear();
  _tasks_done.clear();

  for (size_t i = 0; i < _tasks.size(); i++) {
    if (_tasks[i].getActive()) {
      _tasks_active.push_back(_tasks[i]);
    } else {
      _tasks_done.push_back(_tasks[i]);
    }
  }
}

// protected
void TaskContainer::_sort_priority() {
  vector<Task> *alltasks[3] = {&_tasks_active, &_tasks_done, &_tasks};

  for (size_t v = 0; v < (sizeof(alltasks) / sizeof(*alltasks)); v++) {
    sort((*alltasks[v]).begin(), (*alltasks[v]).end(), cmp_prioroty);
    for (size_t i = 0; i < (*alltasks[v]).size(); i++) {
      (*alltasks[v])[i]._setId(i);
    }
  }
}

// getters
vector<string> TaskContainer::getTags() { return _tags; }

vector<string> TaskContainer::getCategories() { return _categories; }

vector<Task> TaskContainer::getTasks(bool is_active) {
  vector<Task> tasks = (is_active) ? _tasks_active : _tasks_done;
  return tasks;
}

Task *TaskContainer::getTask(size_t index, bool is_active) {
  if (is_active) {
    return &_tasks_active[index];
  } else {
    return &_tasks_done[index];
  }
}

} // namespace tasks
} // namespace toro
