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
  // constructor internals
  void _real_constructor(std::string yyyymmdd);
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

  // getters
  unsigned short getYear();
  unsigned short getMonth();
  unsigned short getDay();

  // Operators
  bool operator==(date &other);
  bool operator>(date &other);
  bool operator<(date &other);
  bool operator>=(date &other);
  bool operator<=(date &other);
  bool operator!=(date &other);

  date &operator=(std::string gnudate);
};

// return code & stdoutput type
struct returnstatus {
  int code;           // return code
  std::string output; // output
};

// config::Config _config type
struct keysset {              // hotkeys
  std::string kb_active_done; // switch between active and done tasks
  std::string kb_task_agenda; // switch between tasklist and agenda
  std::string kb_new_task;    // add new task
};
struct execset {    // executable commands
  std::string rofi; // rofi GUI command
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
