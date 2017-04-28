#include "server_Alumno.h"
#include <string>
#include <vector>
string Alumno::listarInscripciones() const {
    return User::listarInscripciones();
}

string Alumno::inscribir(vector<string> &args) const {
//    1ro una vacante y agrgo un codigo al alummno y un alumno a la materia
//    2ro ins ya realizada: el codigo existia en la lista de alumnos
    if (args.size() < 2){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }
    string materia = args[1];
    string curso = args[2];
    string response = validateMateria(materia, curso);
    if (!response.empty()){ return response; }
    response = generateInscription(materia, curso, id);
    return response;
}

string Alumno::desinscribir(vector<string> &args) const {
  return User::desinscribir(args);
}

Alumno::Alumno(const string &userType, DB &database, const string &id) :
    User(userType, database), id(id) {
    if (! database.userExists(userType, id)){
        throw std::invalid_argument(id + " es un " +userType + " inválido.");
    }
}

string Alumno::print() const {
  return User::print() + " " + id;
}

const string &Alumno::getId() const {
  return id;
}
