#include "logic.hpp"

using namespace std;

namespace toro {
namespace logic {

vector<string> splitString(string astring, string delimiter) {
  vector<string> result;
  size_t pos;

  if (astring.length() > 0) {
    if (astring.find(delimiter) != string::npos) {
      while ((pos = astring.find(delimiter)) != string::npos) {
        result.push_back(astring.substr(0, pos));
        astring.erase(0, pos + delimiter.length());
      }
      result.push_back(astring);
    } else {
      result = {astring};
    }
  } else {
    result = {""};
  }

  return result;
}

string joinString(vector<string> avector, string delimiter) {
  string result;

  if (!avector.empty()) {
    for (size_t s = 0; s < avector.size() - 1; s++) {
      result += avector[s] + delimiter;
    }
    result += avector[avector.size() - 1].c_str();
  }

  return result;
}

string linuxColumns(string astring, string delimiter) {
  string cmd;
  cmd = "echo -e \"" + astring + "\" ";
  cmd += "| column -s $'" + delimiter + "' -t";
  types::returnstatus status = execCommand(cmd);
  return status.output;
}

types::returnstatus execCommand(string acommand) {
  char buffer[128];
  types::returnstatus result{};

  // Open pipe to file
  FILE *pipe = popen(acommand.c_str(), "r");
  if (!pipe) {
    // result.code = 404;
    // return result;
    printf("execCommand: string acommand: %s\n", acommand.c_str());
    throw std::invalid_argument("Incorrect command or PIPE error");
  }

  while (!feof(pipe)) {
    if (fgets(buffer, 128, pipe) != nullptr)
      result.output += buffer;
  }

  result.code = pclose(pipe);
  return result;
}

} // namespace logic
} // namespace toro
