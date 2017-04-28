#include "server_DBException.h"
DBException::DBException(string what_arg) : runtime_error(
    what_arg.c_str()){}