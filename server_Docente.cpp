#include "server_Docente.h"
#include <string>
#include <deque>
#include "server_DB.h"
#define MY_TYPE "docente"
string Docente::listarInscripciones()  {
    string format = User::listarInscripciones();
    return database.listarMateriasCabecera(format, *this);
    //    cout << "listando inscripciones del docente" << endl;
}

Docente::Docente(DB &database, const string &id)
        : User(database), id(id) {
    try {
        database.validateUser(MY_TYPE, id);
    }  catch(DBException& e) {
        throw DBException(id + " es un "+MY_TYPE+" inválido.");
    }
}

string Docente::print() const {
  return "docente " + id;
}
const string &Docente::getId() const {
  return id;
}

void Docente::createInscripcion(std::deque<string> &args) {
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

void Docente::createDesinscripcion(std::deque<string> &args) {
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

