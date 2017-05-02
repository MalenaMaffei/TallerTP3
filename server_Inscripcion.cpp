//#include <iostream>
#include "server_Inscripcion.h"
#include <string>
Inscripcion::Inscripcion(const string &materia, const string &curso,
                         const string &alumnoId)
    : Transaction(materia,curso,alumnoId) {}

void Inscripcion::updateInscriptions(string &inscriptos, string &inscripciones,
                                     string &vacancies) const {
    if (inscripciones.find(materia) != string::npos){
        throw DBException("Inscripción ya realizada.\n");
    }
    int new_vacante = stoi(vacancies) - 1;
    if (new_vacante < 0) {
        throw DBException("El curso "+curso+" de la materia "+materia+ " no "
                "posee mas vacantes.\n");
    }
    inscriptos += " "+alumnoId;
    inscripciones += " "+id;
    vacancies = std::to_string(new_vacante);
}
