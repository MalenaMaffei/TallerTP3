#include "server_Inscripcion.h"
#include <string>
#include <map>
Inscripcion::Inscripcion(const string &materia, const string &curso,
                         const string &alumnoId)
    : Transaction(materia,curso,alumnoId) {}

void Inscripcion::updateInscriptions(std::map<string, string> & materiaInfo)
const {
    string inscriptos = materiaInfo["inscriptos"];
    string vacancies = materiaInfo["vacantes"];
    if (inscriptos.find(alumnoId) != string::npos){
        throw DBException("Inscripción ya realizada.\n");
    }
    int new_vacante = stoi(vacancies) - 1;
    if (new_vacante < 0) {
        throw DBException("El curso "+curso+" de la materia "+materia+ " no "
                "posee mas vacantes.\n");
    }

    inscriptos += " "+alumnoId;
    materiaInfo["inscriptos"] = inscriptos;
    materiaInfo["vacantes"] = std::to_string(new_vacante);
}

