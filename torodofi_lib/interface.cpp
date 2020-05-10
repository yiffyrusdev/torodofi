#include "interface.hpp"
#include "functions.hpp"

using namespace std;

namespace torodofi_lib {
namespace interface {

string strCaption(string add_new_task, string switch_active_done,
                  string switch_task_agenda) {
  string result = "-mesg ";
  result += "\"Have a nice day!\n";
  result += "Use " + color_accent + add_new_task + "</span> ";
  result += "to create new task.\n";
  result += "Use " + color_accent + switch_active_done + "</span> ";
  result += "to view done/active tasks.\n";
  result += "Use " + color_accent + switch_task_agenda + "</span> ";
  result += "to view tasks/agenda. \"";
  return result;
}

Dialog::Dialog() {}

void Dialog::Configure(config::Config aconfig) {
  _config = aconfig;
  _rofi_opts.push_back(_config.pathset.rofi);
  _rofi_opts.push_back(rofi_args);
}

void Dialog::ShowMain() {
  vector<string> rofi_call(_rofi_opts);
  rofi_call.push_back(strCaption(_config.hotkeys.add_new_task,
                                 _config.hotkeys.switch_active_done,
                                 _config.hotkeys.switch_task_agenda));

  string cmd = func::vectorToString(rofi_call);
  printf("%s", cmd.c_str());
  int status = system(cmd.c_str());
}

} // namespace interface
} // namespace torodofi_lib
