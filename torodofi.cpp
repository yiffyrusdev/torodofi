#include <stdio.h>
#include <string>

#include "torodofi/App.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  toro::app::App Application("example.cfg");

  Application.Start();

  return 0;
}
