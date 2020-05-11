#pragma once

#include <stdexcept>
#include <string>

namespace toro {
namespace types {

class date {
protected:
  std::string _gnudate;
  unsigned short _year;
  unsigned short _month;
  unsigned short _day;
  // Check if date valid and pass values to members
  bool _validate_and_pass(unsigned short yyyy, unsigned short mm,
                          unsigned short dd);

public:
  // Empty constructor
  date();
  // 2020-05-11 GNU date format
  date(std::string yyyy_mm_dd_date);
  // 2020,05,11 integers
  date(unsigned year, unsigned month, unsigned day);
  // return constant str like string::c_str()
  const char *c_str() const;
};

} // namespace types
} // namespace toro
