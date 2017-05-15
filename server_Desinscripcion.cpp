#include "server_Desinscripcion.h"
#include <string>
#include <map>
Desinscripcion::Desinscripcion(const string &materia,const string &curso,
                               const string &alumnoId) :
    Transaction(materia,curso,alumnoId) {}


void Desinscripcion::updateInscriptions(std::map<string, string> &materiaInfo)
const {
    string inscriptos = materiaInfo["inscriptos"];
    string vacantes = materiaInfo["vacantes"];

    if (inscriptos.find(alumnoId) == string::npos){
        throw DBException("Inscripción nunca realizada.\n");
    }

    int new_vacante = stoi(vacantes) + 1;
    materiaInfo["vacantes"] = std::to_string(new_vacante);

    int erase_from = inscriptos.find(alumnoId);
    materiaInfo["inscriptos"] = inscriptos.erase(erase_from,alumnoId.size());
}

//void Desinscripcion::updateInscriptions(string &inscriptos,
//                          string &inscripciones, string &vacancies) const {
//    if (inscripciones.find(materia) == string::npos){
//        throw DBException("Inscripción nunca realizada.\n");
//    }
//    int new_vacante = stoi(vacancies) + 1;
//    vacancies = std::to_string(new_vacante);
//
//    int erase_from = inscripciones.find(" "+id);
//    inscripciones.erase(erase_from, id.size()+1);
//
//    erase_from = inscriptos.find(alumnoId);
//    inscriptos.erase(erase_from, alumnoId.size());
//}
