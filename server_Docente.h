#ifndef TP2_DOCENTE_H
#define TP2_DOCENTE_H

#include "server_User.h"
#include <string>

class Docente : public User  {
public:
    Docente(const string &userType, const string &id);

    virtual void listarInscripciones() const;
    virtual void inscribir(string codigo, string curso) const;
    virtual void desinscribir(string codigo, string curso) const;
//    virtual string print() const;

private:
    string id;
};


#endif //TP2_DOCENTE_H
