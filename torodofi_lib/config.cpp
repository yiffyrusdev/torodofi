#include "config.hpp"

using namespace std;

namespace torodofi_lib {
namespace config {

ConfigParser::ConfigParser() {
  _config.hotkeys.switch_task_agenda = "Alt+a";
  _config.hotkeys.switch_active_done = "Alt+Tab";
  _config.hotkeys.add_new_task = "Alt+n";

  _config.pathset.browser = "chromium";
  _config.pathset.notefile = string(getenv("HOME")) + "/ToDo.md";
  _config.pathset.rofi = "rofi";
}

void ConfigParser::_ParseLine(string line) {
  int delimiterindex = line.find(config_format_delimiter);
  string varname;
  string varvalue;

  if (delimiterindex > 0) {
    varname = line.substr(0, delimiterindex);
    varvalue = line.substr(delimiterindex + 2, line.length() + 1);
    if (varname == "switch_active_done")
      _config.hotkeys.switch_active_done = varvalue;
    else if (varname == "switch_task_agenda")
      _config.hotkeys.switch_task_agenda = varvalue;
    else if (varname == "add_new_task")
      _config.hotkeys.add_new_task = varvalue;
    else if (varname == "browser")
      _config.pathset.browser = varvalue;
    else if (varname == "notefile")
      _config.pathset.notefile = varvalue;
    else if (varname == "rofi")
      _config.pathset.rofi = varvalue;
  }
}

void ConfigParser::ReadFile(string afilename) {
  _filename = afilename;
  string line;

  ifstream config(_filename);
  while (getline(config, line)) {
    _ParseLine(line);
  }
}

void ConfigParser::ReadFile(char *afilename) {
  string filename(afilename);
  ReadFile(filename);
}

void ConfigParser::ReRead() { ReadFile(_filename); }

Hotkeys ConfigParser::getHotkeys() { return _config.hotkeys; }
Pathset ConfigParser::getPathset() { return _config.pathset; }
Config ConfigParser::getConfig() { return _config; }
string ConfigParser::getFilename() { return _filename; }
} // namespace config
} // namespace torodofi_lib
