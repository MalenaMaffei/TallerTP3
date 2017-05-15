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

Admin::Admin(DB &database) :
    User(database) {}

string Admin::print() const {
    return MY_TYPE;
}

void Admin::createInscripcion(std::deque<string> &args) {
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
    database.processTransaction(insc, *this);
}

void Admin::createDesinscripcion(std::deque<string> &args) {
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
    database.processTransaction(des, *this);
}

