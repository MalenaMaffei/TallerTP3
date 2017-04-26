#include "server_User.h"
#include "server_UsuariosDB.h"
#include "server_MateriasDB.h"
#include <string>
#include <vector>
#define LISTARMATERIAS "lm"
#define LISTARINSC "li"
#define INS "in"
#define DESINS "de"
#define CODE_POS 0

string User::listarMaterias() const {
//    string format = "$codigo - $descripcion, Curso $curso, "
//        "$docente$iddocente, $vacantes vacantes.\n";
    string format = "$codigo - $descripcion, Curso $curso, "
        "#docente$iddocente, $vacantes vacantes.\n";
    format = materiasDB.listAll(format);
    format = usersDB.fillNameById(format);
    return format;

}

string User::listarInscripciones() const {
    return "<codigo> - <descripcion>, Curso <id-curso>, <nombre-docente>";
}

string User::inscribir(vector<string> args) const {
    return "inscribir de USER";
}

string User::desinscribir(vector<string> args) const {
    return "desinscribir de USER";
}

User::~User() {}

User::User(const string &userType, UsuariosDB &usersDB,MateriasDB &materiasDB) :
            userType(userType), usersDB(usersDB), materiasDB(materiasDB) {}


string User::print() const {
    return userType;
}

string User::executeCommand(vector<string> & commands) const {
    string command = commands[CODE_POS];
    string executed_command;
    if (command == LISTARMATERIAS){
        executed_command = listarMaterias();
    } else if (command == LISTARINSC){
        executed_command = listarInscripciones();
    } else if (command == INS){
//        TODO SACAR PARTE DEL CODIGO
        executed_command = inscribir(commands);
    } else if (command == DESINS){
        executed_command = desinscribir(commands);
    }
    return executed_command;
}
