#include "common_SocketException.h"
SocketException::SocketException(const char* what_arg) : runtime_error(
    what_arg) {

}
