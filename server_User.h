#ifndef TP2_USER_H
#define TP2_USER_H

#include <iostream>
#include <string>
#include <vector>
#include <vector>
#include "server_UsuariosDB.h"
#include "server_MateriasDB.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class User {
public:
    explicit User(const string &userType,
                      UsuariosDB &usersDB,
                      MateriasDB &materiasDB);
    virtual ~User();
    string listarMaterias() const;
    virtual string listarInscripciones() const;
    virtual string inscribir(vector<string> args) const;
    virtual string desinscribir(vector<string> args) const;
    virtual string print() const;
    virtual string executeCommand(vector<string> & commands) const;

private:
    string userType;
    UsuariosDB &usersDB;
    MateriasDB &materiasDB;
};

#endif //TP2_USER_H


