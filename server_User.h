#ifndef TP2_USER_H
#define TP2_USER_H

//#include <iostream>
#include <string>
#include <vector>
#include <deque>
// //#include "server_DB.h"
//#include "server_DBException.h"
#include "server_Inscripcion.h"
#include "server_Desinscripcion.h"
//
class DB;

// using std::cout;
// using std::endl;
//using std::string;
//using std::vector;

class User {
public:
    explicit User(DB &database);
    virtual ~User();
    string listarMaterias() const;
    virtual string listarInscripciones();
    virtual string inscribir(std::deque<string> &args);
    virtual string desinscribir(std::deque<string> &args);
    virtual string print() const = 0;
    virtual string executeCommand(std::deque<string> & commands);

protected:
//  TODO lo que depende de c/uno es crear inscripcion/desins
//    virtual Transaction createInscripcion() = 0;

//  string validateMateria(string materia, string curso) const;
  // virtual string generateInscription(string materia, string curso, string
  // alumnoId);
//  virtual string removeInscription(string materia, string curso,
//                                   string alumnoId) const;
  DB &database;
};

#endif //TP2_USER_H
