#include "functions.hpp"

using namespace std;

namespace torodofi_lib {
namespace func {

string linuxColumn(string astring, string separator) {
  string cmd = "echo -e \"";
  cmd += astring + "\" | column ";
  cmd += "-s $'" + separator + "' -t";
  ReturnStatus returnstatus = execCommand(cmd);

  return returnstatus.content;
}

string vectorToString(vector<string> avector, string dilimiter) {
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

ReturnStatus execCommand(string command) {
  char buffer[128];
  ReturnStatus result;

  // Open pipe to file
  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    result.status = 404;
    return result;
  }

  while (!feof(pipe)) {
    if (fgets(buffer, 128, pipe) != NULL)
      result.content += buffer;
  }

  result.status = pclose(pipe);
  return result;
}
} // namespace func
} // namespace torodofi_lib
