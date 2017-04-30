#include "common_SocketException.h"
#include <string>
SocketException::SocketException(string what_arg) : runtime_error(
    what_arg.c_str()) {}
