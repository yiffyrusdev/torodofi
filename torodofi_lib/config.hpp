#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

namespace torodofi_lib {
const string config_format_delimiter = ": ";

struct Hotkeys {
  string switch_active_done;
  string switch_task_agenda;
  string add_new_task;
};
struct Pathset {
  string rofi;
  string notefile;
  string browser;
};

class Config {
protected:
  Hotkeys _hotkeys;
  Pathset _pathset;

  string _filename;

  void _ParseLine(string line) {
    int delimiterindex = line.find(config_format_delimiter);
    string varname;
    string varvalue;

    if (delimiterindex > 0) {
      varname = line.substr(0, delimiterindex);
      varvalue = line.substr(delimiterindex + 2, line.length() + 1);
      if (varname == "switch_active_done")
        _hotkeys.switch_active_done = varvalue;
      else if (varname == "switch_task_agenda")
        _hotkeys.switch_task_agenda = varvalue;
      else if (varname == "add_new_task")
        _hotkeys.add_new_task = varvalue;
      else if (varname == "browser")
        _pathset.browser = varvalue;
      else if (varname == "notefile")
        _pathset.notefile = varvalue;
      else if (varname == "rofi")
        _pathset.rofi = varvalue;
    }
  }

public:
  Config() {
    _hotkeys.switch_task_agenda = "Alt+a";
    _hotkeys.switch_active_done = "Alt+Tab";
    _hotkeys.add_new_task = "Alt+n";

    _pathset.browser = "chromium";
    _pathset.notefile = string(getenv("HOME")) + "/ToDo.md";
    _pathset.rofi = "rofi";
  }

  void ReadFile(string afilename) {
    _filename = afilename;
    string line;

    ifstream config(_filename);
    while (getline(config, line)) {
      _ParseLine(line);
    }
  }

  void ReadFile(char *afilename) {
    string filename(afilename);
    ReadFile(filename);
  }

  void ReRead() { ReadFile(_filename); }

  Hotkeys getHotkeys() { return _hotkeys; }
  Pathset getPathset() { return _pathset; }
  string getFilename() { return _filename; }
};
} // namespace torodofi_lib
