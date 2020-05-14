#include <stdio.h>
#include <string>

#include "torodofi/App.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  string homedir;

  toro::app::App Application("");

  Application.Start();

  return 0;
}
