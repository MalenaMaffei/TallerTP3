#include <iostream>
#include "server_Inscripcion.h"

Inscripcion::Inscripcion(const string &materia, const string &curso,
                         const string &alumnoId)
    : Transaction(materia,curso,alumnoId) {}

void Inscripcion::updateInscriptions(string &inscriptos, string &inscripciones)
const {

    if (inscripciones.find(materia) != string::npos){
        throw DBException("Inscripción ya realizada.\n");
    }
    inscriptos += " "+alumnoId;
    inscripciones += " "+id;
}

void Inscripcion::updateVacancies(string &vacancy) const {
    int new_vacante = stoi(vacancy) - 1;
    if (new_vacante < 0) {
        throw DBException("El curso "+curso+" de la materia "+materia+ " no "
            "posee más vacantes.\n");
    }
    vacancy = std::to_string(new_vacante);
}
