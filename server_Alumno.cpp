#include "server_Alumno.h"

void Alumno::listarInscripciones() const {
    User::listarInscripciones();
    cout << "listando inscripciones del alumno" << endl;
}

void Alumno::inscribir(string codigo, string curso) const {
    User::inscribir(codigo, curso);
    cout << "inscribir a alumno al curso: "<< curso << " codigo: " << codigo
         << endl;
}

void Alumno::desinscribir(string codigo, string curso) const {
    User::desinscribir(codigo, curso);
    cout << "desinscribir a alumno al curso: "<< curso << " codigo: " << codigo
         << endl;
}
