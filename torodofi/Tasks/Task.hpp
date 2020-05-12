#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "../logic.hpp"
#include "../types.hpp"

namespace toro {
namespace tasks {

const std::string task_start_point = "* ";
const std::string task_field_delimiter = " ";
const std::string task_field_inner_delimiter = ",";

class Task {
protected:
  types::task _task;

  // check either given string is a task determination or not
  std::vector<std::string> _validate_and_pass(std::string teststring);

public:
  Task();
  // pass an .md formatted string:
  // * creation_date expire_date tags categories text
  // * yyyy-mm-dd yyyy-mm-dd tag,tag,tag cat,cat text text text
  Task(std::string taskstring, unsigned priority = 3);
  // Repr task as formatted string for writing to a .md file
  std::string toFileString();
  // Repr task as human-readable formatted string
  // id\t text\t expire_date\t tags\t categories
  std::string toString(std::string delimiter = "\t");
  // getters
  types::task getTask();
  // setters
  void _setId(unsigned aid); // Do not use it if you are not me =)
  void setPriority(unsigned apriority);
  void setExpire(types::date adate);
  void setTags(std::vector<std::string> atags);
  void setCategories(std::vector<std::string> acategories);
  void setText(std::string atext);
};

bool cmp_prioroty(Task &a, Task &b);

} // namespace tasks
} // namespace toro
