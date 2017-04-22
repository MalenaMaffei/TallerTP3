#ifndef TP2_DOCENTE_H
#define TP2_DOCENTE_H

#include "server_User.h"

class Docente : public User  {
public:
    void listarInscripciones() const;
    void inscribir(string codigo, string curso) const;
    void desinscribir(string codigo, string curso) const;

private:
    string id;
};


#endif //TP2_DOCENTE_H
