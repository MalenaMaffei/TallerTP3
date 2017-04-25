#ifndef TP2_DOCENTE_H
#define TP2_DOCENTE_H

#include "server_User.h"
#include <string>
#include <vector>

class Docente : public User  {
public:
    Docente(const string &userType, UsuariosDB &usersDB, const string &id);

    virtual string listarInscripciones() const;
    virtual string inscribir(vector<string> args) const;
    virtual string desinscribir(vector<string> args) const;
    virtual string print() const;
  const string &getId() const;

 private:
    string id;
};


#endif //TP2_DOCENTE_H
