#pragma once

#include <ctime>
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
  bool _bissextile;
  // constructor internals
  void _real_constructor(const std::string& yyyymmdd);
  // Check if date valid and pass values to members
  bool _validate_and_pass(unsigned short yyyy, unsigned short mm,
                          unsigned short dd);

  // 0 - for February of високосный year
  unsigned short _days_in_months[13] = {29, 31, 28, 31, 30, 31, 30,
                                        31, 31, 30, 31, 30, 31};

public:
  // Empty constructor
  date();
  // 2020-05-11 GNU date format
  date(const std::string& yyyy_mm_dd_date);
  // 2020,05,11 integers
  date(unsigned year, unsigned month, unsigned day);

  // Return vector<date> of dates before current
  std::vector<date> vectorBefore(size_t acount);
  // Return vector<date> of dates after current
  std::vector<date> vectorAfter(size_t acount);

  // Return todays date
  static date today();
  // Return GNU date String value
  std::string toString();
  // return constant str like string::c_str()
  const char *c_str() const;

  // getters
  unsigned short getYear() const;
  unsigned short getMonth() const;
  unsigned short getDay() const;

  // Operators
  // do NOT add more than 14 days
  date operator+(unsigned short adays);
  // do NOT add more than 14 days
  date operator-(unsigned short adays);
  date &operator=(const std::string& gnudate);

  bool operator==(const date &two) const;
  bool operator>(const date &two) const;
  bool operator<(const date &two) const;
  bool operator>=(const date &two) const;
  bool operator<=(const date &two) const;
  bool operator!=(const date &two) const;
};

// return code & stdoutput type
struct returnstatus {
  int code;           // return code
  std::string output; // output
};

// config::Config _config type
struct keysset {                 // hotkeys
  std::string kb_active_done;    // switch between active and done tasks
  std::string kb_task_agenda;    // switch between tasklist and agenda
  std::string kb_new_task;       // add new task
  std::string kb_index_modofier; // modifier to choose element by index
};
struct execset {          // executable commands
  std::string rofi;       // rofi GUI command
  std::string urlhandler; // where to open urls
};
struct pathset {        // pathes of files to read
  std::string taskfile; // path to .md file with tasks
};
struct config {
  keysset keys; // hotkeys
  execset exec; // executable commands
  pathset path; // pathes to files to read
};

// tasks::Task _task type
struct task {
  bool is_active; // is task active(true) or done(false)

  unsigned id; // calculates automatically, task string does not contain ID
  unsigned priority; // priority have to be passed in cunstructor as constant

  types::date creation_date;           // date of creation
  types::date expire_date;             // deadline date
  std::vector<std::string> tags;       // marked with tags
  std::vector<std::string> categories; // exist in categories
  std::string url;                     // url assigned with task
  std::string text;                    // task description
};

} // namespace types
} // namespace toro
