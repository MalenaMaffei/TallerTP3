#include "server_Alumno.h"
#include <string>
#include <vector>
string Alumno::listarInscripciones() const {
    return User::listarInscripciones();
//    cout << "listando inscripciones del alumno" << endl;
}

string Alumno::inscribir(vector<string> args) const {
  return User::inscribir(args);
//  cout << "inscribir a alumno al curso: "<< curso << " codigo: " << codigo
//         << endl;
}

string Alumno::desinscribir(vector<string> args) const {
  return User::inscribir(args);
}

Alumno::Alumno(const string &userType, const string &id) : User(userType),
                                                           id(id) {}
string Alumno::print() const {
  return User::print() + " " + id;
}

const string &Alumno::getId() const {
  return id;
}
