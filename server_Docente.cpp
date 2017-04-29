#include "server_Docente.h"
#include "server_DBException.h"
#include <string>
#include <vector>
#include "server_DB.h"
string Docente::listarInscripciones() const {
    return User::listarInscripciones();
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

    try {
        database.newInscription(materia, curso, alumnoId, *this);
        return "Inscripción exitosa.\n";

    } catch (DBException& e){
        return e.what();
    }
}

string Docente::desinscribir(vector<string> &args) const {
  return User::desinscribir(args);
  //    cout  << "desinscribir a un alumno a los cursos del docente" << endl;
}

Docente::Docente(const string &userType,DB &database, const string &id)
        : User(userType, database), id(id) {
    try {
        database.validateUser(userType, id);
    } catch (DBException& e) {
//        por que no podian tener el mismo mensaje de error?!
        throw DBException(id + " es un " +userType + " inválido.");
    }
}

string Docente::print() const {
  return User::print() + " " + id;
}
const string &Docente::getId() const {
  return id;
}
