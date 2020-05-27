#include "App.hpp"

using namespace std;

namespace toro {
namespace app {

// class App
App::App(string aconfigfilename)
    : _objConfig(),
      _objTasks(), active_tasks_caption{}, kb_customs{}, kb_selections{} {
  ifstream file(aconfigfilename.c_str());

  aconfigfilename = (file.good()) ? aconfigfilename : config_file_name;
  file.close();

  _readConfig(aconfigfilename);
  _readTasks(_objConfig.getConfig().path.taskfile);
}

// public

void App::Start() {
  string choice;
  unsigned choice_id;
  types::returnstatus status{};
  bool tmp;

  bool showtasks{true};
  bool showtasks_active{true};

  bool showtask{false};
  bool edittask{false};

  string new_text;
  types::date new_date;
  vector<string> new_tags, new_categories;
  unsigned new_prioroty;

  while (showtasks) {
    _objTasks.sortByPriority(true);
    _objTasks.sortByPriority(false);
    _objTasks.resetIds();
    status = _showTasks(showtasks_active);
    switch (status.code) {
    case 3072: // kb-custom-1
      break;
    case 2816: // kb-custom-2
      new_text = _chooseText("Enter new task text!", "Task");
      new_date = _chooseDate("Choose Deadline!");
      new_tags = _chooseTags("Choose tags for task!");
      new_categories = _chooseCategories("Choose categories for task!");
      new_prioroty = _chooseFromVector(tasks::available_priorities,
                                       "Choose task priority!");
      _objTasks.addTask(new_text, new_date, new_tags, new_categories,
                        new_prioroty);
      break;
    case 2560: // kb-custom-3
      showtasks_active = !showtasks_active;
      break;
    case 0:
      choice = status.output;
      if (choice.length() <= 1) {
        continue;
      }
      choice = choice.substr(0, choice.length() - 1); // remove \n symbol
      if (choice == menu_back) {
        showtasks = false;
      } else {
        // Is it an ugly hack after deleting "< Back" option?
        // Look after "-1"!!!!
        choice_id = atoi(logic::splitString(choice)[0].c_str()) - 1;
        showtask = true;
      }

      while (showtask) {
        showtask = false;
        status = _showOneTask(choice_id, showtasks_active);
        if (status.code == 256) {
          continue;
        }
        if (status.output.length() <= 1) {
          continue;
        }
        choice = status.output;
        choice = choice.substr(0, choice.length() - 1); // remove \n symbol
        if (choice == menu_back) {
          showtask = false;
        } else if (choice == one_task_actions[0]) { // 0 Mark as done
          showtask = false;
          tmp = _objTasks.getTask(choice_id, showtasks_active)->getActive();
          _objTasks.getTask(choice_id, showtasks_active)->setActive(!tmp);
          _objTasks.refreshActiveDone();
          showtasks_active = true;
        } else if (choice == one_task_actions[1]) { // 1 Edit
          showtask = false;
          edittask = true;
        }
      }

      while (edittask) {
        _editTask(choice_id, showtasks_active);
        edittask = false;
      }
      break;
    default:
      _exit();
      return;
    }
  }

  _exit();
}

// protected

void App::_exit() { _objTasks.Dump(); }

types::returnstatus App::_showTasks(bool is_active) {
  vector<tasks::Task> tasks{_objTasks.getTasks(is_active)};
  size_t prio_offset{0}; // any_menu_actions.size(); // FIXME
  types::returnstatus status{};
  string cmd, prompt, caption;
  vector<string> high_priorities, medi_priorities, vstmp;

  for (auto & task : tasks) {
    switch (task.getPriority()) {
    case 1:
      high_priorities.push_back(
          to_string(task.getId() + prio_offset)); // FIXME WRONG COLORING
      break;
    case 2:
      medi_priorities.push_back(to_string(task.getId() + prio_offset));
      break;
    }
  }
  prompt = (is_active) ? "Active" : "Done";
  vstmp = _objTasks.toString(is_active);
  caption = active_tasks_caption + "\n" + color2 + vstmp[0] + span;
  cmd = _caption_based_menu(caption, vstmp[1], prompt, false,
                            kb_customs + kb_selections) +
        " ";
  if (!high_priorities.empty()) {
    cmd += "-u " + logic::joinString(high_priorities, ",") + " ";
  }
  if (!medi_priorities.empty()) {
    cmd += "-a " + logic::joinString(medi_priorities, ",") + " ";
  }
  status = logic::execCommand(cmd);

  return status;
}

types::returnstatus App::_showOneTask(unsigned aid, bool is_active) {
  vector<tasks::Task> tasks{_objTasks.getTasks(is_active)};
  types::returnstatus status{};
  string cmd;

  cmd = _task_based_menu(tasks[aid], one_task_actions, false, kb_selections);
  status = logic::execCommand(cmd);

  return status;
}

void App::_editTask(unsigned aid, bool is_active) {
  tasks::Task *task{_objTasks.getTask(aid, is_active)};
  types::returnstatus status{};
  string cmd;
  string choice, caption, options, prompt;
  vector<string> vstmp;
  unsigned untmp;
  types::date dtmp;

  cmd = _task_based_menu((*task), edit_task_options, false, kb_selections);
  status = logic::execCommand(cmd);

  choice = status.output;
  if (choice.length() <= 1) {
    return;
  }
  choice = choice.substr(0, choice.length() - 1); // remove \n from end line
  if (choice == edit_task_options[0]) {           // 1 Text
    choice = _chooseText(task->getText(), task->getText());
    task->setText(choice);

  } else if (choice == edit_task_options[1]) { // 2 Deadline
    dtmp = _chooseDate("Choose new Deadline:\n", task->getExpire());
    task->setExpire(dtmp);

  } else if (choice == edit_task_options[2]) { // 3 Priority
    untmp = _chooseFromVector(tasks::available_priorities, "Choose priority");
    task->setPriority(untmp);
    //_objTasks.sortByPriority();

  } else if (choice == edit_task_options[3]) { // 4 Tags
    caption =
        "Current: " +
        logic::joinString(task->getTags(), tasks::task_field_inner_delimiter);
    caption += msg0;

    vstmp = _chooseTags(caption);
    if (!vstmp.empty()) {
      task->setTags(vstmp);
    }

  } else if (choice == edit_task_options[4]) { // 5 Categories
    caption =
        "Current: " + logic::joinString(task->getCategories(),
                                        tasks::task_field_inner_delimiter);
    caption += msg0;

    vstmp = _chooseCategories(caption);
    if (!vstmp.empty()) {
      task->setCategories(vstmp);
    }

  } else if (choice == edit_task_options[5]) { // 6 Delete
    _objTasks.delTask(task->getId(), is_active);
    //_objTasks.sortByPriority();
  }
}

string App::_chooseText(string acaption, string atext) {
  string cmd, choice;
  types::returnstatus status{};

  cmd = _caption_based_menu(acaption, atext, "", false);
  cmd += " -filter \"" + atext + "\"";
  status = logic::execCommand(cmd);
  if (status.code == 0) {
    choice = status.output;
    choice = choice.substr(0, choice.length() - 1); // remove \n from end line
  } else {
    choice = atext;
  }

  return choice;
}

types::date App::_chooseDate(std::string acaption, types::date adate) {
  vector<types::date> possible_d{adate.vectorAfter(730)};
  vector<string> possible_s;
  string options, cmd, choice;
  types::returnstatus status{};
  types::date date_choice;

  for (auto & d : possible_d) {
    possible_s.push_back(d.toString());
  }
  options = logic::joinString(possible_s, rofi_options_delimiter);
  cmd = _caption_based_menu(acaption, options, "", false);
  status = logic::execCommand(cmd);
  if (status.code == 0) {
    choice = status.output;
    choice = choice.substr(0, choice.length() - 1); // remove \n from end line
    date_choice = choice;
  } else {
    date_choice = adate;
  }

  return date_choice;
}

vector<string> App::_chooseTags(string acaption) {
  string options, cmd, choice;
  types::returnstatus status{};
  vector<string> tags;

  options = logic::joinString(_objTasks.getTags(), rofi_options_delimiter);
  cmd = _caption_based_menu(acaption, options, "", false);
  cmd += " -multi-select ";
  status = logic::execCommand(cmd);
  if (status.code == 0) {
    choice = status.output;
    choice = choice.substr(0, choice.length() - 1); // remove \n from end line
    tags = logic::splitString(choice, rofi_options_delimiter);
    _objTasks.addTag(tags);
  } else {
    tags = {};
  }

  return tags;
}

vector<string> App::_chooseCategories(string acaption) {
  string options, cmd, choice;
  vector<string> categories;
  types::returnstatus status{};

  options =
      logic::joinString(_objTasks.getCategories(), rofi_options_delimiter);
  cmd = _caption_based_menu(acaption, options, "", false);
  cmd += " -multi-select ";
  status = logic::execCommand(cmd);
  if (status.code == 0) {
    choice = status.output;
    choice = choice.substr(0, choice.length() - 1); // remove \n from end line
    categories = logic::splitString(choice, rofi_options_delimiter);
    _objTasks.addCategory(categories);
  } else {
    categories = {};
  }

  return categories;
}

template <typename T>
T App::_chooseFromVector(vector<T> avector, string acaption) {
  string options, cmd;
  vector<string> svector;
  T choice;
  types::returnstatus status{};

  for (size_t i = 0; i < avector.size(); i++) {
    svector.push_back(to_string(avector[i]));
  }
  options = logic::joinString(svector, rofi_options_delimiter);
  cmd = _caption_based_menu(acaption, options, "", false, "-format \"i\"");
  status = logic::execCommand(cmd);
  if (status.code == 0) {
    choice = avector[atoi(status.output.c_str())];
  } else {
    choice = T();
  }

  return choice;
}

string App::_task_based_menu(tasks::Task atask, vector<string> add_menu,
                             bool any_menu, string custom_rofi_keys) {
  types::config _config{_objConfig.getConfig()};
  string cmd;
  vector<string> caption;

  caption = {
      atask.getText() + " " + color3 + atask.getCreation().toString() + span,
      "Deadline: " + color1 + atask.getExpire().toString() + span,
      "Tags: " +
          logic::joinString(atask.getTags(), tasks::task_field_inner_delimiter),
      "Categories: " + logic::joinString(atask.getCategories(),
                                         tasks::task_field_inner_delimiter),
  };

  cmd += "echo -e \"";
  if (any_menu && !any_menu_actions.empty()) {
    cmd += logic::joinString(any_menu_actions, rofi_options_delimiter) +
           rofi_options_delimiter;
  }
  cmd += logic::joinString(add_menu, rofi_options_delimiter) +
         rofi_options_delimiter;

  cmd += "\" | ";
  cmd += _config.exec.rofi + " ";
  cmd += custom_rofi_keys;
  cmd += "-dmenu -p \"Task\" ";
  cmd += "-mesg \"" + logic::joinString(caption, "\n") + "\"";

  return cmd;
}

string App::_caption_based_menu(string acaption, string add_menu,
                                string aprompt, bool any_menu,
                                string custom_rofi_keys) {
  types::config _config{_objConfig.getConfig()};
  string cmd;

  cmd = "echo -e \"";
  if (any_menu && !any_menu_actions.empty()) {
    cmd += logic::joinString(any_menu_actions, rofi_options_delimiter) +
           rofi_options_delimiter;
  }
  cmd += add_menu + "\" | ";
  cmd += _config.exec.rofi + " " + custom_rofi_keys + " ";
  cmd += "-dmenu -p \"" + aprompt + "\" ";
  cmd += "-mesg \"" + acaption + "\"";

  return cmd;
}

void App::_readConfig(string afilename) {
  ifstream file(afilename);
  if (!file.good()) {
    file.close();
    ofstream file(afilename);
    file << endl;
    file.close();
    string cmd = _objConfig.getConfig().exec.rofi + " -e \"";
    cmd += " No config file with was found. Empty file was created: ";
    cmd += config_file_name + "\n ";
    cmd += "Press Enter to continue\"\n";
    logic::execCommand(cmd);
  }

  _objConfig.readFile(afilename);
  types::config _config = _objConfig.getConfig();

  active_tasks_caption = "Have a nice day!\n";
  active_tasks_caption +=
      color0 + _config.keys.kb_new_task + span + " to add new task. ";
  active_tasks_caption +=
      color0 + _config.keys.kb_active_done + span + " to view done tasks. ";
  active_tasks_caption +=
      color0 + _config.keys.kb_task_agenda + span + " to view agenda. ";
  active_tasks_caption += color0 + _config.keys.kb_index_modofier + "'ID'" +
                          span + " to select item 1-9 with hotkey. ";
  active_tasks_caption += color0 + "Esc" + span + " to return back.\n";

  kb_customs =
      " -kb-custom-1 \"" + _objConfig.getConfig().keys.kb_active_done + "\"";
  kb_customs +=
      " -kb-custom-2 \"" + _objConfig.getConfig().keys.kb_new_task + "\"";
  kb_customs +=
      " -kb-custom-3 \"" + _objConfig.getConfig().keys.kb_task_agenda + "\"";

  kb_selections = "";
  for (size_t k = 1; k < 10; k++) {
    kb_selections += " -kb-select-" + to_string(k);
    kb_selections +=
        " \"" + _config.keys.kb_index_modofier + to_string(k) + "\" ";
  }
}

void App::_readTasks(string afilename) {
  ifstream file(afilename);
  if (!file.good()) {
    file.close();
    ofstream file(afilename);
    file << endl;
    file.close();
    string cmd = _objConfig.getConfig().exec.rofi + " -e \"";
    cmd += " No MarkDown file with tasks was found. Empty file was created: ";
    cmd += home_directory + "/example.md\n ";
    cmd += "Press Enter to continue\"\n";
    logic::execCommand(cmd);
  }
  _objTasks.readFile(afilename);
}

} // namespace app
} // namespace toro
