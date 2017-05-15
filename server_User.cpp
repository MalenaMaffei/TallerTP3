#include "server_User.h"
#include <string>
#include <vector>
#include <deque>

// #include "server_DBException.h"
#define LISTARMATERIAS "lm"
#define LISTARINSC "li"
#define INS "in"
#define DESINS "de"
//#define CODE_POS 0
#include "server_DB.h"

using std::deque;

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



string User::inscribir(deque<string> &args) {
//    Inscripcion insc = createInscripcion(args);
    try {
        createInscripcion(args);
//        sendTransaction(insc);
//        database.processTransaction(insc, *this);
        return "Inscripción exitosa.\n";
    } catch(DBException& e){
        return e.what();
    }
}

string User::desinscribir(deque<string> &args) {
//    Desinscripcion des = createDesinscripcion(args);
    try {
        createDesinscripcion(args);
//        sendTransaction(des);
//        database.processTransaction(des, *this);
        return "Desinscripción exitosa.\n";
    }catch(DBPermissionException& e){
        return e.what();
    } catch(DBException& e){
        return "Desinscripción inválida.\n";
    }
}

User::~User() {}

User::User(DB &database) : database(database) {}

string User::executeCommand(deque<string> & commands)  {
//    TODO lanzar error con comando invalido
    string command = commands.front();
    commands.pop_front();
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
