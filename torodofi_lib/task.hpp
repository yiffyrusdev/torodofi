#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

namespace torodofi_lib {
namespace task {

const std::string task_format_delimiter = "* ";
const std::string task_prority_delimiter = "## ";
const std::string task_field_delimiter = ".,.";

struct SingleTask {
  int priority;

  std::string text;
  std::string creation_date;
  std::string expire_date;

  std::vector<std::string> tags;
  std::vector<std::string> categories;
};

bool compareByPriority(const SingleTask &a, const SingleTask &b);

std::string vectorToString(std::vector<std::string> avector,
                           std::string dilimiter = " ");

std::vector<std::string> stringToVector(std::string astring,
                                        std::string delimiter);

class TaskContainer {
protected:
  std::vector<SingleTask> _tasks;
  std::string _filename;

  void _ParseLine(std::string aline, int apriority);

  std::string _ComposeTaskString(SingleTask task);

  std::string _ComposePrioString(SingleTask task);

  void _SortContainer();

public:
  void ReadFile(std::string afilename);

  void DumpToFile(std::string afilename = "");

  void ReadFile(char *afilename);

  void DumpToFile(char *afilename);

  void ReRead();

  std::vector<SingleTask> getTasks();
};
} // namespace task
} // namespace torodofi_lib
