#include "server_Docente.h"
#include <string>
#include <vector>
string Docente::listarInscripciones() const {
    return User::listarInscripciones();
//    cout << "listando inscripciones del docente" << endl;
}

string Docente::inscribir(vector<string> &args) const {
    if (args.size() < 3){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }

    string alumnoId = args[1];
    string materia = args[2];
    string curso = args[3];

    string response = validateMateria(materia, curso);
    if (!response.empty()){ return response; }
    if (!database.userExists("alumno", alumnoId)){
        return "El alumno "+alumnoId+" es inválido.\n";
    }
    if (!database.docenteTeachesMateria(materia, curso, id)){
        return "No tiene permisos para operar sobre "+materia+", curso "
            ""+curso+".\n";
    }
    response = generateInscription(materia, curso, alumnoId);
    return response;
}

string Docente::desinscribir(vector<string> &args) const {
  return User::desinscribir(args);
  //    cout  << "desinscribir a un alumno a los cursos del docente" << endl;
}

Docente::Docente(const string &userType,DB &database, const string &id)
        : User(userType, database), id(id) {
    if (! database.userExists(userType, id)){
        throw std::invalid_argument(id + " es un " +userType + " inválido.");
    }
}

string Docente::print() const {
  return User::print() + " " + id;
}
const string &Docente::getId() const {
  return id;
}

