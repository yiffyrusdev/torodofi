#include "torodofi_config.h"

#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  Config config;
  config.ReadFile("config");
  return 0;
}
