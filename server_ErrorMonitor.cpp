#include <iostream>
#include <string>
#include "server_ErrorMonitor.h"
using std::cerr;
using std::endl;

void ErrorMonitor::outputError(string error) const {
  cerr << error << endl;
}
