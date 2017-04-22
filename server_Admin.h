#ifndef TP2_SERVER_ADMIN_H
#define TP2_SERVER_ADMIN_H
#include "server_User.h"


class Admin : public User {
    void listarInscripciones() const;
    void inscribir(string codigo, string curso) const;
    void desinscribir(string codigo, string curso) const;

};


#endif //TP2_SERVER_ADMIN_H
