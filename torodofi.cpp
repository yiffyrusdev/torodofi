#include <string>

#include "torodofi/App.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  printf("Please, check out GIT repository! Tasks.md file format has been changed! Now uses '- [x]' style");
  toro::app::App Application("");
  Application.Start();

  return 0;
}
