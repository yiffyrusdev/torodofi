#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

namespace torodofi_lib {
namespace task {

const string task_format_delimiter = "* ";
const string task_prority_delimiter = "## ";
const string task_field_delimiter = ".,.";

struct SingleTask {
  int priority;

  string text;
  string creation_date;
  string expire_date;

  vector<string> tags;
  vector<string> categories;
};

bool compareByPriority(const SingleTask &a, const SingleTask &b);

string vectorToString(vector<string> avector, string dilimiter = " ");

vector<string> stringToVector(string astring, string delimiter);

class TaskContainer {
protected:
  vector<SingleTask> _tasks;
  string _filename;

  void _ParseLine(string aline, int apriority);

  string _ComposeTaskString(SingleTask task);

  string _ComposePrioString(SingleTask task);

  void _SortContainer();

public:
  void ReadFile(string afilename);

  void DumpToFile(string afilename = "");

  void ReadFile(char *afilename);

  void DumpToFile(char *afilename);

  void ReRead();

  vector<SingleTask> getTasks();
};
} // namespace task
} // namespace torodofi_lib
