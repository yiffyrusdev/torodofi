#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

string task_format_delimiter = "* ";
string task_prority_delimiter = "## ";
string task_field_delimiter = ".,.";

struct SingleTask {
  int priority;

  string text;
  string creation_date;
  string expire_date;

  vector<string> tags;
  vector<string> categories;
};

bool compareByPriority(const SingleTask &a, const SingleTask &b) {
  return a.priority < b.priority;
}

string vectorToString(vector<string> avector, string dilimiter = " ") {
  string result;
  for (size_t i = 0; i < avector.size(); i++)
    result += avector[i] + dilimiter;
  return result;
}

vector<string> stringToVector(string astring, string delimiter) {
  size_t pos;
  string token;
  vector<string> parsed_line;

  while ((pos = astring.find(delimiter)) != string::npos) {
    token = astring.substr(0, pos);
    parsed_line.push_back(token);
    astring.erase(0, pos + delimiter.length());
  }

  return parsed_line;
}

class TaskContainer {
protected:
  vector<SingleTask> _tasks;
  string _filename;

  void _ParseLine(string aline, int apriority) {
    vector<string> parsed_line;
    vector<string> tags_categories;

    int del = aline.find(task_format_delimiter);

    if (del == 0) {
      _tasks.push_back(SingleTask());

      aline = aline.substr(task_format_delimiter.length());
      parsed_line = stringToVector(aline, task_field_delimiter);

      _tasks.back().categories = stringToVector(parsed_line.back(), " ");
      parsed_line.pop_back();
      _tasks.back().tags = stringToVector(parsed_line.back(), " ");
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

  string _ComposeTaskString(SingleTask task) {
    string result = task_format_delimiter;

    result += task.text + task_field_delimiter;
    result += task.creation_date + task_field_delimiter;
    result += task.expire_date + task_field_delimiter;
    result += vectorToString(task.tags) + task_field_delimiter;
    result += vectorToString(task.categories) + task_field_delimiter;
    return result;
  }

  string _ComposePrioString(SingleTask task) {
    string result = task_prority_delimiter;
    result += to_string(task.priority);
    return result;
  }

  void _SortContainer() {
    sort(_tasks.begin(), _tasks.end(), compareByPriority);
  }

public:
  void ReadFile(string afilename) {
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

  void DumpToFile(string afilename = "") {
    if (afilename == "")
      afilename = _filename;

    int priority;

    ofstream task_file(afilename);
    if (task_file.is_open()) {
      for (size_t t = 0; t < _tasks.size(); t++) {
        if (_tasks[t].priority != priority)
          task_file << _ComposePrioString(_tasks[t]) << endl;
        task_file << _ComposeTaskString(_tasks[t]) << endl;
      }
    } else {
      printf("IO ERROR!!!");
    }
  }

  void ReadFile(char *afilename) { ReadFile(string(afilename)); }

  void DumpToFile(char *afilename) { DumpToFile(string(afilename)); }

  void ReRead() { ReadFile(_filename); }

  vector<SingleTask> getTasks() { return _tasks; }
};
