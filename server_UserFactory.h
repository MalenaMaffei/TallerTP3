#ifndef TP2_USERFACTORY_H
#define TP2_USERFACTORY_H

#include "server_User.h"
#include <string>
#include <vector>

using std::vector;
class UserFactory {
public:
//    va a devolver puntero a usuario para poder usar polimorfismo.
//MUCHO CUIDADO  voy a tener que liberar esto cuando termine la sesion
  User *createUser(vector<string> &params, DB &database) const;
};


#endif //TP2_USERFACTORY_H
