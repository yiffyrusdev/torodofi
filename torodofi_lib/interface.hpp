#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

#include "config.hpp"
#include "functions.hpp"
#include "task.hpp"

using namespace std;

namespace torodofi {
namespace interface {

const string menu_back = "";

struct DialogContent {
  string caption;
  vector<string> options;
};

class Dialog {
protected:
  DialogContent _main_dialog;
  config::Config _config;
  vector<string> _rofi_opts;
  string _rofi_list;

  string _StrCaption();
  string _StrTask(task::SingleTask atask);
  vector<string> _VecTask(vector<task::SingleTask> atasks);
  string _StrPriorities(vector<task::SingleTask> atasks);

  string _TaskCaption(task::SingleTask atask);
  vector<string> _TaskOptions(task::SingleTask atask);

public:
  Dialog();
  void Configure(config::Config aconfig);
  func::ReturnStatus ShowMain(vector<task::SingleTask> atasks);
  func::ReturnStatus ShowTask(task::SingleTask atask);
};
} // namespace interface
} // namespace torodofi
