#include "common_SocketException.h"
#include <string>
SocketException::SocketException(string what_arg, int fD) : runtime_error(
    (what_arg + ", file descriptor: " +  std::to_string(fD)).c_str()) {}
