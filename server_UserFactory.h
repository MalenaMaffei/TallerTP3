#ifndef TP2_USERFACTORY_H
#define TP2_USERFACTORY_H
#include "server_User.h"
#include <string>
#include <deque>

class UserFactory {
public:
  User *createUser(std::deque<string> &params, DB &database) const;
};


#endif //TP2_USERFACTORY_H
