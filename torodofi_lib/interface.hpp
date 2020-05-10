#include <string>
#include <vector>

#include "config.hpp"

using namespace std;

namespace torodofi_lib {

struct DialogContent {
  string caption;
  vector<string> options;
};

class Dialog {
protected:
  DialogContent _dialog;
  config::Config _config;

public:
  Dialog(config::Config aconfig) { _config = aconfig; }
};
} // namespace torodofi_lib
