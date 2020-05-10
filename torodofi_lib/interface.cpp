#include "interface.hpp"

using namespace std;

namespace torodofi_lib {
namespace interface {

string Dialog::strCaption() {
  string result = "-mesg ";
  result += "\"Have a nice day!\n";
  result += "Use " + color_accent + _config.hotkeys.add_new_task + "</span> ";
  result += "to create new task.\n";
  result +=
      "Use " + color_accent + _config.hotkeys.switch_active_done + "</span> ";
  result += "to view done/active tasks.\n";
  result +=
      "Use " + color_accent + _config.hotkeys.switch_task_agenda + "</span> ";
  result += "to view tasks/agenda. \"";
  return result;
}

string Dialog::strTask(task::SingleTask atask) {
  string result;
  result += atask.text + " ";
  result += atask.expire_date + " ";
  result += func::vectorToString(atask.tags) + " ";
  result += func::vectorToString(atask.categories) + " ";
  return result + "\n";
}

vector<string> Dialog::vecTask(vector<task::SingleTask> atasks) {
  vector<string> result;
  result.push_back("\"");

  for (size_t i = 0; i < atasks.size(); i++) {
    result.push_back(strTask(atasks[i]));
  }

  result.push_back("\" | ");
  return result;
}

Dialog::Dialog() {}

void Dialog::Configure(config::Config aconfig) {
  _config = aconfig;
  _rofi_opts.push_back(_config.pathset.rofi);
  _rofi_opts.push_back(rofi_args);

  _rofi_list.push_back(pre_rofi_list);
}

func::ReturnStatus Dialog::ShowMain(vector<task::SingleTask> atasks) {
  vector<string> opt_list = vecTask(atasks);
  vector<string> rofi_list(_rofi_list);
  vector<string> rofi_opts(_rofi_opts);

  rofi_list.insert(rofi_list.end(), opt_list.begin(), opt_list.end());

  vector<string> rofi_call(rofi_list);
  rofi_call.insert(rofi_call.end(), rofi_opts.begin(), rofi_opts.end());
  rofi_call.push_back(strCaption());

  string cmd = func::vectorToString(rofi_call);
  func::ReturnStatus status = func::execCommand(cmd.c_str());
  return status;
}

} // namespace interface
} // namespace torodofi_lib
