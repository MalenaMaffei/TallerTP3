#include "server_Alumno.h"
#include <string>
#include <vector>
#include "server_DBException.h"
#include "server_DB.h"

string Alumno::listarInscripciones() const {
    return User::listarInscripciones();
}

string Alumno::inscribir(vector<string> &args)  {
    if (args.size() < 2){
        throw std::invalid_argument("Comando inscripción no recibió argumentos "
                                        "suficientes");
    }
    string materia = args[1];
    string curso = args[2];
        try {
            database.newInscription(materia, curso, id, *this);
            return "Inscripción exitosa.\n";

        } catch (DBException& e){
            return e.what();
        }
}

string Alumno::desinscribir(vector<string> &args) const {
  return User::desinscribir(args);
}

Alumno::Alumno(const string &userType, DB &database, const string &id) :
    User(userType, database), id(id) {
    try {
        this->database.validateUser(userType, id);
    } catch (DBException& e) {
//        por que no podian tener el mismo mensaje de error?!
        throw DBException(id + " es un " +userType + " inválido.");
    }
}

string Alumno::print() const {
  return User::print() + " " + id;
}

const string &Alumno::getId() const {
  return id;
}
