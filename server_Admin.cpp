#include "server_Admin.h"
#include <string>
#include <vector>
#include "server_DB.h"

string Admin::listarInscripciones() const {
    return User::listarInscripciones();
//    cout << "listando inscripciones de todo el mundo" << endl;
}

string Admin::inscribir(vector<string> &args) {
    if (args.size() < 3){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }
    string alumnoId = args[1];
    string materia = args[2];
    string curso = args[3];
        try {
            database.newInscription(materia, curso, alumnoId, *this);
            return "Inscripción exitosa.\n";

        } catch (DBException& e){
            return e.what();
        }
}

string Admin::desinscribir(vector<string> &args) const {
    return User::desinscribir(args);
//    cout << "desinscribir a cualquiera del curso: " << curso << endl;
}

Admin::Admin(const string &userType, DB &database) :
    User(userType, database) {}
