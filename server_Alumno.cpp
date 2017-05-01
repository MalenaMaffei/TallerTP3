#include "server_Alumno.h"
#include <string>
#include <vector>
#include "server_DBException.h"
#include "server_DB.h"
#define MY_TYPE "alumno"
string Alumno::listarInscripciones() {
    string format = User::listarInscripciones();
    return database.listarMateriasCabecera(format, *this);
}

string Alumno::inscribir(vector<string> &args)  {
    if (args.size() < 2){
        throw std::invalid_argument("Comando inscripción no recibió argumentos "
                                        "suficientes");
    }
    string materia = args[1];
    string curso = args[2];
    Inscripcion insc(materia, curso, id);
        try {
            database.processTransaction(insc, *this);
            return "Inscripción exitosa.\n";
        } catch(DBException& e){
            return e.what();
        }
}

string Alumno::desinscribir(vector<string> &args) {
    if (args.size() < 2){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }

    string materia = args[1];
    string curso = args[2];
    Desinscripcion des(materia, curso, id);
    try {
        database.processTransaction(des, *this);
        return "Desinscripción exitosa.\n";
    } catch(DBException& e){
        return "Desinscripción inválida.\n";
    }
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
