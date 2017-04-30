#ifndef TP2_SERVER_ADMIN_H
#define TP2_SERVER_ADMIN_H
#include "server_User.h"
#include <string>
#include <vector>
class Admin : public User {
public:
    explicit Admin(DB &database);
    virtual string listarInscripciones() const;
    virtual string inscribir(vector<string> &args);
    virtual string desinscribir(vector<string> &args);
    virtual string print() const;
};


#endif //TP2_SERVER_ADMIN_H
