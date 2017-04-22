#ifndef TP2_ALUMNO_H
#define TP2_ALUMNO_H
#include "server_User.h"


class Alumno : public User {
public:
    void listarInscripciones() const;
    void inscribir(string codigo, string curso) const;
    void desinscribir(string codigo, string curso) const;

private:
    string id;

};


#endif //TP2_ALUMNO_H
