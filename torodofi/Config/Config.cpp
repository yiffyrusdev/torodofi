#include "Config.hpp"

using namespace std;

namespace toro {
namespace config {

// Config
void Config::_Config() {
  _config.exec.rofi = "rofi";
  _config.keys.kb_active_done = "Alt+a";
  _config.keys.kb_new_task = "Alt+n";
  _config.keys.kb_task_agenda = "Alt+a";
  _config.keys.kb_index_modofier = "Alt+";
  _config.path.taskfile = "example.md";
}
Config::Config() { _Config(); }
Config::Config(string afilename) {
  _Config();
  readFile(afilename);
}

// Config public
void Config::readFile(string afilename) {
  size_t var_del_len = var_delimiter.length();
  string line;
  bool passed;
  ifstream file(afilename);

  if (file.is_open()) {
    while (getline(file, line)) {
      if (line.find(var_delimiter) > 0) {
        passed = _validate_and_pass_line(line);
      }
    }
  } else {
    printf("config::readFile: string afilename: %s", afilename.c_str());
    throw std::invalid_argument("Could not open file to read");
  }
}

types::config Config::getConfig() { return _config; }

// Config protected
bool Config::_validate_and_pass_line(string aline) {
  vector<string> parsed_line = logic::splitString(aline, var_delimiter);
  string var, val;

  if (parsed_line.size() == 2) {
    var = parsed_line[0];
    val = parsed_line[1];
    if (var == "kb_active_done") {
      _config.keys.kb_active_done = val;
    } else if (var == "kb_task_agenda") {
      _config.keys.kb_task_agenda = val;
    } else if (var == "kb_new_task") {
      _config.keys.kb_new_task = val;
    } else if (var == "kb_index_modofier") {
      _config.keys.kb_index_modofier = val;
    } else if (var == "rofi") {
      _config.exec.rofi = val;
    } else if (var == "taskfile") {
      _config.path.taskfile = val;
    }
    return true;
  } else {
    return false;
  }
}

} // namespace config
} // namespace toro
