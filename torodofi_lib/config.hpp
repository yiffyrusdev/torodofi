#pragma once

#include <fstream>
#include <stdio.h>
#include <string>

namespace torodofi_lib {
namespace config {
const std::string config_format_delimiter = ": ";

struct Hotkeys {
  std::string switch_active_done;
  std::string switch_task_agenda;
  std::string add_new_task;
};
struct Pathset {
  std::string rofi;
  std::string notefile;
  std::string browser;
};

struct Config {
  Hotkeys hotkeys;
  Pathset pathset;
};

class ConfigParser {
protected:
  Config _config;

  std::string _filename;

  void _ParseLine(std::string line);

public:
  ConfigParser();

  void ReadFile(std::string afilename);
  void ReadFile(char *afilename);

  void ReRead();

  Hotkeys getHotkeys();
  Pathset getPathset();
  Config getConfig();
  std::string getFilename();
};
} // namespace config
} // namespace torodofi_lib
