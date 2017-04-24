#include "server_Docente.h"
#include <string>
#include <vector>
string Docente::listarInscripciones() const {
    return User::listarInscripciones();
//    cout << "listando inscripciones del docente" << endl;
}

string Docente::inscribir(vector<string> args) const {
  return User::inscribir(args);
//  cout << "inscribir a un alumno a los cursos del docente" << endl;
}

string Docente::desinscribir(vector<string> args) const {
  return User::desinscribir(args);
  //    cout  << "desinscribir a un alumno a los cursos del docente" << endl;
}

Docente::Docente(const string &userType, const string &id) : User(userType),
                                                             id(id) {}

string Docente::print() const {
  return User::print() + " " + id;
}
const string &Docente::getId() const {
  return id;
}

