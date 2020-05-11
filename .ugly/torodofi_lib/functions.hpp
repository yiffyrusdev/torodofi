#pragma once

#include <string>
#include <vector>

using namespace std;

namespace torodofi {
namespace func {
struct ReturnStatus {
  int status;
  string content;
};

string linuxColumn(string avector, string separator = "\t");

string vectorToString(vector<string> avector, string dilimiter = " ");
vector<string> stringToVector(string astring, string delimiter = " ");

ReturnStatus execCommand(string command);
} // namespace func
} // namespace torodofi
