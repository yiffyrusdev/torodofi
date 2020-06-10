#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "types.hpp"

namespace toro {
namespace logic {

// execute command and get return code and stdout both
types::returnstatus execCommand(const std::string& acommand);
// function to split string by delimiter
std::vector<std::string> splitString(std::string astring,
                                     const std::string& delimiter = " ");
// function to join vector of strings into one vector
std::string joinString(std::vector<std::string> avector,
                       const std::string& delimiter = " ");
// function to align strings separated by '\n' to a table
std::string linuxColumns(const std::string& astring, const std::string& delimiter = "\t");
} // namespace logic
} // namespace toro
