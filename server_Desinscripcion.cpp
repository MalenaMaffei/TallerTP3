#include <regex>
#include "server_Desinscripcion.h"
#include <string>
Desinscripcion::Desinscripcion(const string &materia,const string &curso,
                               const string &alumnoId) :
    Transaction(materia,curso,alumnoId) {}


void Desinscripcion::updateInscriptions(string &inscriptos,
                               string &inscripciones, string &vacancies) const {
    if (inscripciones.find(materia) == string::npos){
        throw DBException("Inscripción nunca realizada.\n");
    }
    int new_vacante = stoi(vacancies) + 1;
    vacancies = std::to_string(new_vacante);
    inscripciones = std::regex_replace(inscripciones,std::regex(" "+id),"");
    inscriptos = std::regex_replace(inscriptos,std::regex(alumnoId), "");
}
