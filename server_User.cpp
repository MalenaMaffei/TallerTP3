#include "server_User.h"
#include <string>

void User::listarMaterias() const {
//    manda al CLIENTE la respuesta del servidor.
    cout << "listando todas las materias" << endl;
}

void User::listarInscripciones() const {
//    manda al CLIENTE la respuesta del servidor.
    cout << "listando todas las inscripciones desde USER" << endl;
}

void User::inscribir(string codigo, string curso) const {
//    manda al CLIENTE la respuesta del servidor.
    cout << "inscribir de USER" << endl;
}

void User::desinscribir(string codigo, string curso) const {
//    nada todavia
    cout << "desinscribir de USER" << endl;
}

User::~User() {}

User::User(const string &userType) : userType(userType) {}

string User::print() const {
    return userType;
}
