#pragma once

#include <string>
#include <vector>

namespace torodofi_lib {
namespace func {
std::string vectorToString(std::vector<std::string> avector,
                           std::string dilimiter = " ");
std::vector<std::string> stringToVector(std::string astring,
                                        std::string delimiter = " ");
} // namespace func
} // namespace torodofi_lib
