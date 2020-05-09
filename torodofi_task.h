#include <fstream>
#include <string>
#include <vector>

#include <stdio.h>

using namespace std;

string task_format_delimiter = "* ";
string task_field_delimiter = "<$";

struct SingleTask {
  unsigned int priority;

  string text;
  string creation_date;
  string expire_date;

  vector<string> tags;
  vector<string> categories;
};

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

  void _ParseLine(string line) {
    int delimiterindex = line.find(task_format_delimiter);
    vector<string> parsed_line;
    vector<string> tags_categories;

    if (delimiterindex >= 0) {
      _tasks.push_back(SingleTask());

      parsed_line = _ParseVector(line, task_field_delimiter);

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
      _tasks.back().priority = atoi(parsed_line.back().c_str());
      parsed_line.pop_back();
    }
  }

public:
  void ReadFile(string afilename) {
    _filename = afilename;
    string line;

    ifstream tasks(_filename);
    while (getline(tasks, line)) {
      _ParseLine(line);
    }
  }

  void ReadFile(char *afilename) { ReadFile(string(afilename)); }

  void ReRead() { ReadFile(_filename); }

  vector<SingleTask> getTasks() { return _tasks; }
};
