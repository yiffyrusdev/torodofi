#include <stdio.h>
#include <string>

#include "torodofi/App.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  string homedir;

  homedir = getenv("HOME");
  toro::app::App Application(homedir + "/.config/torodofi.conf");

  Application.Start();

  return 0;
}
