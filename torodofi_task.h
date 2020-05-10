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
  return a.priority > b.priority;
}

class TaskContainer {
protected:
  vector<SingleTask> _tasks;
  string _filename;

  vector<string> _ParseVector(string line, string delimiter) {
    size_t pos;
    string token;
    vector<string> parsed_line;

    while ((pos = line.find(delimiter)) != string::npos) {
      token = line.substr(0, pos);
      parsed_line.push_back(token);
      line.erase(0, pos + task_format_delimiter.length());
    }

    return parsed_line;
  }

  void _ParseLine(string aline, int apriority) {
    vector<string> parsed_line;
    vector<string> tags_categories;

    int del = aline.find(task_format_delimiter);

    if (del == 0) {
      _tasks.push_back(SingleTask());

      aline = aline.substr(task_format_delimiter.length());
      parsed_line = _ParseVector(aline, task_field_delimiter);

      _tasks.back().categories = _ParseVector(parsed_line.back(), " ");
      parsed_line.pop_back();
      _tasks.back().tags = _ParseVector(parsed_line.back(), " ");
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

    while (getline(task_file, line)) {
      ipriority = line.find(task_prority_delimiter);
      if (ipriority == 0)
        curr_priority =
            atoi(line.substr(ipriority + delim_len, ipriority + delim_len + 2)
                     .c_str());

      _ParseLine(line, curr_priority);
    }
    _SortContainer();
  }

  void DumpToFile(string afilename) {}

  void ReadFile(char *afilename) { ReadFile(string(afilename)); }

  void DumpToFile(char *afilename) { DumpToFile(string(afilename)); }

  void ReRead() { ReadFile(_filename); }

  vector<SingleTask> getTasks() { return _tasks; }
};
