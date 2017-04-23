#include "server_Admin.h"
#include <string>
void Admin::listarInscripciones() const {
//    User::listarInscripciones();
    cout << "listando inscripciones de todo el mundo" << endl;
}

void Admin::inscribir(string codigo, string curso) const {
//    User::inscribir(codigo, curso);
    cout << "inscribir a cualquiera al curso" << endl;
}

void Admin::desinscribir(string codigo, string curso) const {
//    User::desinscribir(codigo, curso);
    cout << "desinscribir a cualquiera del curso: " << curso << endl;
}
