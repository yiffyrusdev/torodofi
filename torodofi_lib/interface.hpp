#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

#include "config.hpp"
#include "functions.hpp"
#include "task.hpp"

using namespace std;

namespace torodofi_lib {
namespace interface {

const string rofi_args = "-regex -tokenize -i -no-levenshtein-sort \"$@\"";
const string pre_rofi_list = "echo -e ";

const string color_accent = "<span color='#2d7ed8'>";

struct DialogContent {
  string caption;
  vector<string> options;
};

class Dialog {
protected:
  DialogContent _main_dialog;
  config::Config _config;
  vector<string> _rofi_opts;
  vector<string> _rofi_list;

  string strCaption();
  string strTask(task::SingleTask atask);
  vector<string> vecTask(vector<task::SingleTask> atasks);
  string strPriorities(vector<task::SingleTask> atasks);

public:
  Dialog();
  void Configure(config::Config aconfig);
  func::ReturnStatus ShowMain(vector<task::SingleTask> atasks);
  void ShowTask();
};
} // namespace interface
} // namespace torodofi_lib
