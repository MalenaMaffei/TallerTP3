#ifndef TP2_SERVER_ADMIN_H
#define TP2_SERVER_ADMIN_H
#include "server_User.h"
#include <string>

class Admin : public User {
public:
    virtual void listarInscripciones() const;
    virtual void inscribir(string codigo, string curso) const;
    virtual void desinscribir(string codigo, string curso) const;
};


#endif //TP2_SERVER_ADMIN_H
