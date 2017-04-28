#include "server_Admin.h"
#include <string>
#include <vector>
string Admin::listarInscripciones() const {
    return User::listarInscripciones();
//    cout << "listando inscripciones de todo el mundo" << endl;
}

string Admin::inscribir(vector<string> &args) const {
    if (args.size() < 3){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }
    string alumnoId = args[1];
    string materia = args[2];
    string curso = args[3];
    return generateInscription(materia, curso, alumnoId);
}

string Admin::desinscribir(vector<string> &args) const {
    return User::desinscribir(args);
//    cout << "desinscribir a cualquiera del curso: " << curso << endl;
}

Admin::Admin(const string &userType, DB &database) :
    User(userType, database) {}

