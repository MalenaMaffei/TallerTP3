#include "server_DBException.h"
#include <string>
DBException::DBException(string what_arg) : runtime_error(
    what_arg.c_str()){}

DBPermissionException::DBPermissionException(const string &what_arg)
    : DBException(what_arg) {}
