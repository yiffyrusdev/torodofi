#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

#include "config.hpp"

using namespace std;

namespace torodofi_lib {
namespace interface {

const string rofi_args = "-regex -tokenize -i";

const string color_accent = "<span color='#2d7ed8'>";

string strCaption(string add_new_task, string switch_active_done,
                  string switch_task_agenda);

struct DialogContent {
  string caption;
  vector<string> options;
};

class Dialog {
protected:
  DialogContent _main_dialog;
  config::Config _config;
  vector<string> _rofi_opts;

public:
  Dialog();
  void Configure(config::Config aconfig);
  void ShowMain();
  void ShowTask();
};
} // namespace interface
} // namespace torodofi_lib
