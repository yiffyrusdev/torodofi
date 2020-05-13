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

const std::string no_tag = "---";       // Normal if no tags
const std::string no_category = "---";  // Normal if no categoried
const std::string empty_tag = ".";      // This is anomal tag! Caused by err
const std::string empty_category = "."; // This is anomal tag! Caused by err

const std::vector<unsigned> available_priorities = {1, 2, 3};

class Task {
protected:
  types::task _task;

  // check either given string is a task determination or not
  std::vector<std::string> _validate_and_pass(std::string teststring);

public:
  Task();
  // pass all task parameters
  Task(std::string atext, types::date expire, std::vector<std::string> atags,
       std::vector<std::string> acategories, unsigned apriority);
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
  unsigned getPriority();
  unsigned getId();
  std::string getText();
  types::date getCreation();
  types::date getExpire();
  std::vector<std::string> getTags();
  std::vector<std::string> getCategories();
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
