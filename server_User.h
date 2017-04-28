#ifndef TP2_USER_H
#define TP2_USER_H

#include <iostream>
#include <string>
#include <vector>
#include <vector>
#include "server_DB.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class User {
public:
    explicit User(const string &userType, DB &database);
    virtual ~User();
    string listarMaterias() const;
    virtual string listarInscripciones() const;
    virtual string inscribir(vector<string> &args) const = 0;
    virtual string desinscribir(vector<string> &args) const;
    virtual string print() const;
    virtual string executeCommand(vector<string> & commands) const;

protected:
  string validateMateria(string materia, string curso) const;
  virtual string generateInscription(string materia, string curso, string
  alumnoId) const;
  string userType;
  DB &database;

private:


//    UsuariosDB &usersDB;
//    MateriasDB &materiasDB;
};

#endif //TP2_USER_H


