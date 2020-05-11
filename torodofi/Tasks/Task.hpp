#pragma once

#include <string>
#include <vector>

using namespace std;

namespace toro {
namespace tasks {

class Task {
protected:
  unsigned id; // calculates automatically, task string does not contain ID
  unsigned priority; // priority have to be passed in cunstructor as constant

  string text;
};

} // namespace tasks
} // namespace toro
