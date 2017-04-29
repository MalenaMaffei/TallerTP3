#include "server_Admin.h"
#include <string>
#include <vector>
#include "server_DB.h"
#define MY_TYPE "admin"
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
    Inscripcion insc(materia, curso, alumnoId);
        try {
            database.processTransaction(insc, *this);
            return "Inscripción exitosa.\n";

        } catch (DBException& e){
            return e.what();
        }
}

string Admin::desinscribir(vector<string> &args) {
    if (args.size() < 3){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }

    string alumnoId = args[1];
    string materia = args[2];
    string curso = args[3];
    Desinscripcion des(materia, curso, alumnoId);
    try {
        database.processTransaction(des, *this);
        return "Desinscripción exitosa.\n";

    } catch (DBException& e){
        return "Desinscripción inválida.\n";
    }
}

Admin::Admin(DB &database) :
    User(database) {}

string Admin::print() const {
    return MY_TYPE;
}
