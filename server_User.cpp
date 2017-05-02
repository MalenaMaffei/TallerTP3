#include "server_User.h"
#include <string>
#include <vector>
// #include "server_DBException.h"
#define LISTARMATERIAS "lm"
#define LISTARINSC "li"
#define INS "in"
#define DESINS "de"
#define CODE_POS 0
#include "server_DB.h"

string User::listarMaterias() const {
    string format = "$codigo - $descripcion, Curso $curso, "
        "#docente$iddocente, $vacantes vacantes.\n";
    format = database.fillAllMaterias(format);
//    format = database.fillNameById(format);
    return format;
}

string User::listarInscripciones() {
    return "$codigo - $descripcion, Curso $curso, #docente$iddocente.\n";
}



string User::inscribir(vector<string> &args) {
    if (args.size() < 2){
        throw std::invalid_argument("Comando inscripcion no recibió argumentos "
                                        "suficientes");
    }
    return "hola de user base";
}

string User::desinscribir(vector<string> &args) {
    return "hola";
}

User::~User() {}

User::User(DB &database) : database(database) {}

string User::executeCommand(vector<string> & commands)  {
//    TODO lanzar error con comando invalido
    string command = commands[CODE_POS];
    string executed_command;
    if (command == LISTARMATERIAS){
        executed_command = listarMaterias();
    } else if (command == LISTARINSC){
        executed_command = listarInscripciones();
    } else if (command == INS){
//        TODO SACAR PARTE DEL CODIGO
        executed_command =
            inscribir(commands);
    } else if (command == DESINS){
        executed_command = desinscribir(commands);
    } else {
        executed_command = command + " es un comando inválido.\n";
    }
    return executed_command;
}
