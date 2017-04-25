#ifndef TP2_SOCKETEXCEPTION_H
#define TP2_SOCKETEXCEPTION_H

#include <exception>
#include <stdexcept>

class SocketException : public std::runtime_error {
public:
  SocketException(const char* what_arg);
};

#endif //TP2_SOCKETEXCEPTION_H
