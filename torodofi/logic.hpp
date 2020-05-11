#pragma once

#include <string>
#include <vector>

namespace toro {
namespace logic {

// function to split string by delimiter
std::vector<std::string> splitString(std::string astring,
                                     std::string delimiter = " ");
// function to join vector of strings into one vector
std::string joinString(std::vector<std::string> avector,
                       std::string delimiter = " ");

} // namespace logic
} // namespace toro
