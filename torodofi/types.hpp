#pragma once

#include <stdexcept>
#include <string>
#include <vector>

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

  // Return GNU date String value
  std::string toString();
  // return constant str like string::c_str()
  const char *c_str() const;
};

struct task {
  unsigned id; // calculates automatically, task string does not contain ID
  unsigned priority; // priority have to be passed in cunstructor as constant
  types::date creation_date;           // date of creation
  types::date expire_date;             // deadline date
  std::vector<std::string> tags;       // marked with tags
  std::vector<std::string> categories; // exist in categories
  std::string text;                    // task description
};

} // namespace types
} // namespace toro
