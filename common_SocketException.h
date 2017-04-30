#ifndef TP2_SOCKETEXCEPTION_H
#define TP2_SOCKETEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

using std::string;
class SocketException : public std::runtime_error {
public:
  explicit SocketException(string what_arg);
};

#endif //TP2_SOCKETEXCEPTION_H
