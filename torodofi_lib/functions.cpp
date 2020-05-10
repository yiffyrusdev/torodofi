#include "functions.hpp"

using namespace std;

namespace torodofi_lib {
namespace func {
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
} // namespace func
} // namespace torodofi_lib
