#include "interface.hpp"

using namespace std;

namespace torodofi {
namespace interface {

const string rofi_args = "-regex -tokenize -i -no-levenshtein-sort \"$@\"";
// Must be accurate! Amount of specified here menu options
// Is used in Dialog::strPriorities as hard-coded value!
const string pre_rofi_list = "echo -e \"" + menu_back;
const string color_accent = "<span color='#2d7ed8'>";
const string color_urgent = "<span color='#ff7ed8'>";
const string color_decent = "<span color='#626262'>";
const string spaces = "                                                        "
                      "                                                       ";

// Dialog class

Dialog::Dialog() {}

// protected
string Dialog::_StrCaption() {
  string result = "-mesg ";
  result += "\"Have a nice day!\n";
  result += "Use " + color_accent + _config.hotkeys.add_new_task + "</span> ";
  result += "to create new task.\n";
  result +=
      "Use " + color_accent + _config.hotkeys.switch_active_done + "</span> ";
  result += "to view done/active tasks.\n";
  result +=
      "Use " + color_accent + _config.hotkeys.switch_task_agenda + "</span> ";
  result += "to view tasks/agenda.";
  return result + "\"";
}

string Dialog::_StrTask(task::SingleTask atask) {
  string result;
  result += atask.text + "\t";
  result += atask.expire_date + "\t";
  result += func::vectorToString(atask.tags) + "\t";
  result += func::vectorToString(atask.categories) + "\t";
  result += spaces + "id:" + to_string(atask.id);
  return result + "\n";
}

vector<string> Dialog::_VecTask(vector<task::SingleTask> atasks) {
  string alltasks = "";
  vector<string> result;

  for (size_t i = 0; i < atasks.size(); i++) {
    alltasks += _StrTask(atasks[i]);
  }
  result.push_back(func::linuxColumn(alltasks));
  result.push_back("\" | ");

  return result;
}

string Dialog::_StrPriorities(vector<task::SingleTask> atasks) {
  string result;
  string tmp;
  vector<string> first_prio;
  vector<string> second_prio;
  for (size_t t = 0; t < atasks.size(); t++) {
    switch (atasks[t].priority) {
    case 1:
      first_prio.push_back(to_string(t + 0)); // see def of pre_rofi_args
      break;
    case 2:
      second_prio.push_back(to_string(t + 0)); // see def of pre_rofi_args
      break;
    }
  }

  tmp = func::vectorToString(first_prio, ",");
  tmp = tmp.substr(0, tmp.length() - 1);
  result += "-u " + tmp + " ";
  tmp = func::vectorToString(second_prio, ",");
  tmp = tmp.substr(0, tmp.length() - 1);
  result += "-a " + tmp + " ";

  return result;
}

string Dialog::_TaskCaption(task::SingleTask atask) {
  string result = "-mesg \"";
  result += color_accent + atask.text + "</span>";
  result += color_decent + "(" + atask.creation_date + ")</span>\n";
  result += "Deadline: " + color_urgent + atask.expire_date + "</span>\n";
  result += "Tags: " + func::vectorToString(atask.tags) + "\n";
  result += "Categories: " + func::vectorToString(atask.categories);
  return result + "\"";
}

vector<string> Dialog::_TaskOptions(task::SingleTask atask) {
  vector<string> result;
  result.push_back("1. Mark as Done\n");
  result.push_back("2. Edit\n");
  result.push_back("\" |");
  return result;
}

// public

void Dialog::Configure(config::Config aconfig) {
  _config = aconfig;
  _rofi_opts.push_back(_config.pathset.rofi);
  _rofi_opts.push_back(rofi_args);

  _rofi_list = pre_rofi_list;
}

func::ReturnStatus Dialog::ShowMain(vector<task::SingleTask> atasks) {
  string rofi_list(_rofi_list);
  vector<string> rofi_opts(_rofi_opts);

  string opt_list = func::vectorToString(_VecTask(atasks));
  rofi_list += opt_list;

  vector<string> rofi_call;
  rofi_call.push_back(rofi_list);
  rofi_call.insert(rofi_call.end(), rofi_opts.begin(), rofi_opts.end());
  rofi_call.push_back(_StrPriorities(atasks));
  rofi_call.push_back(_StrCaption());
  rofi_call.push_back("-dmenu -p \"todo\"");

  string cmd = func::vectorToString(rofi_call, " ");
  func::ReturnStatus status = func::execCommand(cmd.c_str());
  return status;
}

func::ReturnStatus Dialog::ShowTask(task::SingleTask atask) {
  string rofi_list(_rofi_list);
  vector<string> rofi_opts(_rofi_opts);
  vector<string> tedit_opts = _TaskOptions(atask);
  rofi_list += func::vectorToString(tedit_opts, "");

  vector<string> rofi_call;
  rofi_call.push_back(rofi_list);
  rofi_call.insert(rofi_call.end(), rofi_opts.begin(), rofi_opts.end());
  rofi_call.push_back(_TaskCaption(atask));
  rofi_call.push_back("-dmenu -p \"Task:\"");

  string cmd = func::vectorToString(rofi_call, " ");
  func::ReturnStatus status = func::execCommand(cmd.c_str());
  return status;
}

} // namespace interface
} // namespace torodofi
