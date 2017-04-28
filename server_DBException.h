#ifndef TP2_DB_EXCEPTION_H
#define TP2_DB_EXCEPTION_H
#include <exception>
#include <stdexcept>
#include <string>
using std::string;

class DBException : public std::runtime_error  {

 public:
  DBException(string what_arg);
};

#endif //TP2_DB_EXCEPTION_H
