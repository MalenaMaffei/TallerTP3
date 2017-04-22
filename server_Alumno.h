#ifndef TP2_ALUMNO_H
#define TP2_ALUMNO_H
#include "server_User.h"


class Alumno : public User {
    void listarInscripciones() const;
    void inscribir(string codigo, string curso) const;
    void desinscribir(string codigo, string curso) const;

};


#endif //TP2_ALUMNO_H
