#include "server_Admin.h"
#include <string>
//#include <vector>
#include <deque>
#include "server_DB.h"
#define MY_TYPE "admin"
string Admin::listarInscripciones() {
    string format = User::listarInscripciones();
    return database.listarMateriasCabecera(format, *this);
//    cout << "listando inscripciones de todo el mundo" << endl;
}

string Admin::inscribir(std::deque<string> &args) {
    if (args.size() < 3){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }
    string alumnoId = args.front();
    args.pop_front();
    string materia = args.front();
    args.pop_front();
    string curso = args.front();
    args.pop_front();
    Inscripcion insc(materia, curso, alumnoId);
        try {
            database.processTransaction(insc, *this);
            return "Inscripción exitosa.\n";
        } catch(DBException& e){
            return e.what();
        }
}

string Admin::desinscribir(std::deque<string> &args) {
    if (args.size() < 3){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }

    string alumnoId = args.front();
    args.pop_front();
    string materia = args.front();
    args.pop_front();
    string curso = args.front();
    args.pop_front();
    Desinscripcion des(materia, curso, alumnoId);
    try {
        database.processTransaction(des, *this);
        return "Desinscripción exitosa.\n";
    } catch(DBException& e){
        return "Desinscripción inválida.\n";
    }
}

Admin::Admin(DB &database) :
    User(database) {}

string Admin::print() const {
    return MY_TYPE;
}
