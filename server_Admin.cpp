#include "server_Admin.h"
#include <string>
#include <vector>
string Admin::listarInscripciones() const {
    return User::listarInscripciones();
//    cout << "listando inscripciones de todo el mundo" << endl;
}

string Admin::inscribir(vector<string> args) const {
    return User::inscribir(args);
//    cout << "inscribir a cualquiera al curso" << endl;
}

string Admin::desinscribir(vector<string> args) const {
    return User::desinscribir(args);
//    cout << "desinscribir a cualquiera del curso: " << curso << endl;
}

Admin::Admin(const string &userType, DB &database) :
    User(userType, database) {}

