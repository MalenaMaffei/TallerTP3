#include "server_Alumno.h"
#include <string>
#include <deque>
#include "server_DBException.h"
#include "server_DB.h"
#define MY_TYPE "alumno"
string Alumno::listarInscripciones() {
    string format = User::listarInscripciones();
    return database.listarMateriasCabecera(format, *this);
}

Alumno::Alumno(DB &database, const string &id) :
    User(database), id(id) {
    try {
        this->database.validateUser(MY_TYPE, id);
    } catch(DBException& e) {
//        por que no podian tener el mismo mensaje de error?!
        throw DBException(id + " es un " +MY_TYPE + " inválido.");
    }
}

string Alumno::print() const {
  return "alumno " + id;
}

const string &Alumno::getId() const {
  return id;
}

void Alumno::createInscripcion(std::deque<string> &args) {
    if (args.size() < 2){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }
    string materia = args.front();
    args.pop_front();
    string curso = args.front();
    args.pop_front();
    Inscripcion insc(materia, curso, id);
    database.processTransaction(insc, *this);
}

void Alumno::createDesinscripcion(std::deque<string> &args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }
    string materia = args.front();
    args.pop_front();
    string curso = args.front();
    args.pop_front();
    Desinscripcion des(materia, curso, id);
    database.processTransaction(des, *this);
}

bool Alumno::hasPermissions(std::string materia) {
//    return database.validatePermissions(materia, *this);
    return database.validatePermissions(materia, *this);
}

