#include <regex>
#include "server_Desinscripcion.h"
Desinscripcion::Desinscripcion(const string &materia,const string &curso,
                               const string &alumnoId) :
    Transaction(materia,curso,alumnoId) {}


void Desinscripcion::updateInscriptions(string &inscriptos,
                                        string &inscripciones) const {

    if (inscripciones.find(materia) == string::npos){
        throw DBException("Inscripción nunca realizada.\n");
    }
    inscripciones = std::regex_replace(inscripciones,std::regex(" "+id),"");
    inscriptos = std::regex_replace(inscriptos,std::regex(alumnoId), "");

}

void Desinscripcion::updateVacancies(string &vacancy) const {
    int new_vacante = stoi(vacancy) + 1;
    vacancy = std::to_string(new_vacante);
}

