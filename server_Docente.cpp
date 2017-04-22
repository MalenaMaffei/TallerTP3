#include "server_Docente.h"

void Docente::listarInscripciones() const {
    User::listarInscripciones();
    cout << "listando inscripciones del docente" << endl;
}

void Docente::inscribir(string codigo, string curso) const {
    User::inscribir(codigo, curso);
    cout << "inscribir a un alumno a los cursos del docente" << endl;
}

void Docente::desinscribir(string codigo, string curso) const {
    User::desinscribir(codigo, curso);
    cout  << "desinscribir a un alumno a los cursos del docente" << endl;
}
