#include "server_Alumno.h"
#include <string>
#include <vector>
string Alumno::listarInscripciones() const {
    return User::listarInscripciones();
}

string Alumno::inscribir(vector<string> args) const {
  return User::inscribir(args);
}

string Alumno::desinscribir(vector<string> args) const {
  return User::inscribir(args);
}

Alumno::Alumno(const string &userType, server_UsuariosDB &usersDB,const string &id) :
        User(userType,usersDB),id(id) {
    if (! usersDB.userExists(userType, id)){
        throw std::invalid_argument(id + " es un " +userType + " inválido.");
    }
}

string Alumno::print() const {
  return User::print() + " " + id;
}

const string &Alumno::getId() const {
  return id;
}
