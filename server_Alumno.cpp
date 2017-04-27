#include "server_Alumno.h"
#include <string>
#include <vector>
string Alumno::listarInscripciones() const {
    return User::listarInscripciones();
}

string Alumno::inscribir(vector<string> args) const {
//    1ro una vacante y agrgo un codigo al alummno y un alumno a la materia
//    2ro ins ya realizada: el codigo existia en la lista de alumnos
//    3ro materia no valida -> Base
//    4to curso no valido -> Base
//    5to curso sin vacantes -> base
//    en realidad la parte de incribir o des lo polimorfico son las validaciones
  return User::inscribir(args);
}

string Alumno::desinscribir(vector<string> args) const {
  return User::inscribir(args);
}

Alumno::Alumno(const string &userType, DB &database, const string &id) :
    User(userType, database), id(id) {
    if (! database.userExists(userType, id)){
        throw std::invalid_argument(id + " es un " +userType + " inválido.");
    }
}

string Alumno::print() const {
  return User::print() + " " + id;
}

const string &Alumno::getId() const {
  return id;
}
