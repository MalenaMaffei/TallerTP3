#include "server_Docente.h"
#include "server_DBException.h"
#include <string>
#include <vector>
#include "server_DB.h"
#define MY_TYPE "docente"
string Docente::listarInscripciones()  {
    string format = User::listarInscripciones();
    return database.listarMateriasCabecera(format, *this);
    //    cout << "listando inscripciones del docente" << endl;
}

string Docente::inscribir(vector<string> &args)  {
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
    } catch(DBException& e){
        return e.what();
    }
}

string Docente::desinscribir(vector<string> &args) {
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
    } catch(DBPermissionException& e){
        return e.what();
    } catch(DBException& e){
        return "Desinscripción inválida.\n";
    }
}

Docente::Docente(DB &database, const string &id)
        : User(database), id(id) {
    try {
        database.validateUser(MY_TYPE, id);
    }  catch(DBException& e) {
//        por que no podian tener el mismo mensaje de error?!
        throw DBException(id + " es un "+MY_TYPE+" inválido.");
    }
}

string Docente::print() const {
  return "docente " + id;
}
const string &Docente::getId() const {
  return id;
}
