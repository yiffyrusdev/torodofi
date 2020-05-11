#include <string>
#include <vector>

#include "logic.hpp"

using namespace std;

namespace toro {
namespace logic {

vector<string> splitString(string astring, string delimiter) {
  vector<string> result;
  size_t pos;

  while ((pos = astring.find(delimiter)) != string::npos) {
    result.push_back(astring.substr(0, pos));
    astring.erase(0, pos + delimiter.length());
  }
  result.push_back(astring);

  return result;
}

string joinString(vector<string> avector, string delimiter) {
  string result;

  for (size_t s = 0; s < avector.size() - 1; s++) {
    result += avector[s] + delimiter;
  }
  result += avector[avector.size() - 1];

  return result;
}

} // namespace logic
} // namespace toro
