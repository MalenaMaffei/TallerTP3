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
    format = database.fillNameById(format);
    return format;

}

string User::listarInscripciones() const {
    return "<codigo> - <descripcion>, Curso <id-curso>, <nombre-docente>";
}



string User::inscribir(vector<string> &args) {
   // if (args.size() < 2){
   //     throw std::invalid_argument("Comando inscripcion no recibió argumentos "
   //                                     "suficientes");
   // }
   // string materia = args[1];
   // string curso = args[2];
   // return validateMateria(materia, curso);
   return "hola";
}

string User::desinscribir(vector<string> &args) const {
    return "hola";
}

User::~User() {}

User::User(const string &userType, DB &database) :
            userType(userType), database(database) {}


string User::print() const {
    return userType;
}

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
    }
    return executed_command;
}

//string User::validateMateria(string materia, string curso) const {
//
//    return "";
//}

// string User::generateInscription(string materia, string curso,
//                                  string alumnoId) {
//     try {
//         database.newInscription(materia, curso, alumnoId, *this);
//         return "Inscripción exitosa.\n";
//
//     } catch (DBException& e){
//         return e.what();
//     }
// }

string User::removeInscription(string materia, string curso,
                               string alumnoId) const {
    if (!database.materiaExists(materia)) {
        return "Desinscripción inválida.\n";
    }
//    else if (!database.cursoExists(materia, curso)) {
//        return "Desinscripción inválida.\n";
//    }
    return "hola";
//    bool success = database.removeInscription;
}
