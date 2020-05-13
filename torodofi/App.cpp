#include "App.hpp"

using namespace std;

namespace toro {
namespace app {

// class App
App::App(string aconfigfilename) {
  _readConfig(aconfigfilename);
  _readTasks(_objConfig.getConfig().path.taskfile);
}

// public

void App::Start() {
  string choice;
  unsigned choice_id;
  types::returnstatus status;

  bool showactive = true;
  bool showtask = false;
  bool edittask = false;

  string new_text;
  types::date new_date;
  vector<string> new_tags, new_categories;
  unsigned new_prioroty;

  while (showactive) {
    status = _showActiveTasks();
    printf("%d\n", status.code);
    switch (status.code) {
    case 10: // kb-custom-1
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
    case 12: // kb-custom-3
      break;
    case 0:
      choice = status.output;
      choice = choice.substr(0, choice.length() - 1); // remove \n symbol
      if (choice == menu_back) {
        showactive = false;
      } else {
        choice_id = atoi(logic::splitString(choice)[0].c_str());
        showtask = true;
      }

      while (showtask) {
        status = _showOneTask(choice_id);
        choice = status.output;
        choice = choice.substr(0, choice.length() - 1); // remove \n symbol
        if (choice == menu_back) {
          showtask = false;
        } else if (choice == one_task_actions[0]) { // 0 Mark as done
          showtask = true;
        } else if (choice == one_task_actions[1]) { // 1 Edit
          showtask = false;
          edittask = true;
        }
      }

      while (edittask) {
        _editTask(choice_id);
        edittask = false; // thats why if choice == menu_back is unneeded
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

types::returnstatus App::_showActiveTasks() {
  vector<tasks::Task> tasks = _objTasks.getTasks();
  size_t prio_offset = any_menu_actions.size();
  types::returnstatus status;
  string cmd;
  vector<string> high_priorities;
  vector<string> medi_priorities;
  unsigned task_priority;

  // Tasts already sorted by priority!
  for (size_t t = 0; t < tasks.size(); t++) {
    string cmd;

    switch (tasks[t].getPriority()) {
    case 1:
      high_priorities.push_back(to_string(tasks[t].getId() + prio_offset));
      break;
    case 2:
      medi_priorities.push_back(to_string(tasks[t].getId() + prio_offset));
      break;
    }
  }
  cmd = _caption_based_menu(active_tasks_caption, _objTasks.toString(),
                            "Active", true, kb_customs) +
        " ";
  cmd += "-u " + logic::joinString(high_priorities, ",") + " ";
  cmd += "-a " + logic::joinString(medi_priorities, ",") + " ";
  status = logic::execCommand(cmd);

  return status;
}

types::returnstatus App::_showOneTask(unsigned aid) {
  vector<tasks::Task> tasks = _objTasks.getTasks();
  types::returnstatus status;
  string cmd;

  cmd = _task_based_menu(tasks[aid], one_task_actions);
  status = logic::execCommand(cmd);

  return status;
}

void App::_editTask(unsigned aid) {
  tasks::Task *task = _objTasks.getTask(aid);
  types::returnstatus status;
  string cmd;
  string choice, caption, options, prompt;
  vector<string> vstmp;
  unsigned untmp;
  types::date dtmp;

  cmd = _task_based_menu((*task), edit_task_options);
  status = logic::execCommand(cmd);

  choice = status.output;
  choice = choice.substr(0, choice.length() - 1); // remove \n from end line
  if (choice == edit_task_options[0]) {           // 0 Text
    choice = _chooseText(task->getText(), task->getText());
    task->setText(choice);

  } else if (choice == edit_task_options[1]) { // 1 Deadline
    dtmp = _chooseDate("Choose new Deadline:\n", task->getExpire());
    task->setExpire(dtmp);

  } else if (choice == edit_task_options[2]) { // Priority
    untmp = _chooseFromVector(tasks::available_priorities, "Choose priority");
    task->setPriority(untmp);
    _objTasks.sortByPriority();

  } else if (choice == edit_task_options[3]) { // 3 Tags
    caption =
        "Current: " +
        logic::joinString(task->getTags(), tasks::task_field_inner_delimiter);
    caption += msg0;

    vstmp = _chooseTags(caption);
    if (vstmp.size() > 0) {
      task->setTags(vstmp);
    }

  } else if (choice == edit_task_options[4]) { // 4 Categories
    caption =
        "Current: " + logic::joinString(task->getCategories(),
                                        tasks::task_field_inner_delimiter);
    caption += msg0;

    vstmp = _chooseCategories(caption);
    if (vstmp.size() > 0) {
      task->setCategories(vstmp);
    }

  } else if (choice == edit_task_options[5]) { // 5 Delete
    _objTasks.delTask(task->getId());
  }
}

string App::_chooseText(string acaption, string atext) {
  string cmd, choice;
  types::returnstatus status;

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
  vector<types::date> possible_d = adate.vectorAfter(730);
  vector<string> possible_s;
  string options, cmd, choice;
  types::returnstatus status;
  types::date date_choice;

  for (size_t d = 0; d < possible_d.size(); d++) {
    possible_s.push_back(possible_d[d].toString());
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
  types::returnstatus status;
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
  types::returnstatus status;

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
//
T App::_chooseFromVector(vector<T> avector, string acaption) {
  string options, cmd;
  vector<string> svector;
  T choice;
  types::returnstatus status;

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

string App::_task_based_menu(tasks::Task atask, vector<string> add_menu) {
  types::config _config = _objConfig.getConfig();
  string cmd;
  vector<string> caption;

  caption = {
      atask.getText() + " " + atask.getCreation().toString(),
      "Deadline: " + atask.getExpire().toString(),
      "Tags: " +
          logic::joinString(atask.getTags(), tasks::task_field_inner_delimiter),
      "Categories: " + logic::joinString(atask.getCategories(),
                                         tasks::task_field_inner_delimiter),
  };

  cmd += "echo -e \"";
  cmd += logic::joinString(any_menu_actions, rofi_options_delimiter) +
         rofi_options_delimiter;
  cmd += logic::joinString(add_menu, rofi_options_delimiter) +
         rofi_options_delimiter;

  cmd += "\" | ";
  cmd += _config.exec.rofi + " ";
  cmd += "-dmenu -p \"Task\" ";
  cmd += "-mesg \"" + logic::joinString(caption, "\n") + "\"";

  return cmd;
}

string App::_caption_based_menu(string acaption, string add_menu,
                                string aprompt, bool any_menu,
                                string custom_rofi_keys) {
  types::config _config = _objConfig.getConfig();
  string cmd;

  cmd = "echo -e \"";
  if (any_menu) {
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
  _objConfig.readFile(afilename);
  types::config _config = _objConfig.getConfig();

  active_tasks_caption = "Have a nice day!\n";
  active_tasks_caption += _config.keys.kb_new_task + "to add new task\n";
  active_tasks_caption += _config.keys.kb_active_done + "to view done tasks\n";
  active_tasks_caption += _config.keys.kb_task_agenda + "to view agenda";

  kb_customs =
      " -kb-custom-1 \"" + _objConfig.getConfig().keys.kb_active_done + "\"";
  kb_customs +=
      " -kb-custom-2 \"" + _objConfig.getConfig().keys.kb_new_task + "\"";
  kb_customs +=
      " -kb-custom-3 \"" + _objConfig.getConfig().keys.kb_task_agenda + "\"";
}

void App::_readTasks(string afilename) { _objTasks.readFile(afilename); }

} // namespace app
} // namespace toro
