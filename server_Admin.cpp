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
    string response = validateMateria(materia, curso);
    if (!response.empty()){ return response; }
    if (!database.userExists("alumno", alumnoId)){
        return "El alumno "+alumnoId+" es inválido.\n";
    }
    response = generateInscription(materia, curso, alumnoId);
    return response;
}

string Admin::desinscribir(vector<string> &args) const {
    return User::desinscribir(args);
//    cout << "desinscribir a cualquiera del curso: " << curso << endl;
}

Admin::Admin(const string &userType, DB &database) :
    User(userType, database) {}

