#include "common_Socket.h"
#include <string>
#include <cstring>
#include <regex>
#include "server_User.h"
#include "server_Admin.h"
#include "server_Docente.h"
#include "server_Alumno.h"
#include "server_Session.h"
#include "server_MateriasDB.h"

#define BACKLOG 10
#define BUFFSIZE 300
#define READ_SHTDWN 1
#define SERVER_MODE 0
#define LENGTH_SIZE 4


int server(const char *server_port, string usersFile, string materiasFile){
    ErrorMonitor errorMonitor;
    Socket socket;

//    std::string str("hello $name");
//    str = std::regex_replace(str, std::regex("\\$name"), "Somename");
//    cout << "intento regex debed decir hello somename" << str << endl;
    string line = "blah blah $vacante balh $docente$iddocente, sdasd ";
//    string line = "blah blah $vacante balh, sdasd ";

    std::regex rgx(".*\\$(\\w+).*");
    std::smatch match;
    while (std::regex_search(line, match, rgx)) {
        cout << match[0] << endl;
        line = match.suffix();
    }
//    std::regex_search(line, match, rgx);
//    std::cout << "match: " << match[1] << std::endl;
//    std::cout << "match: " << match[2] << std::endl;



    socket.Create(0, server_port, SERVER_MODE);

//  TODO el server tiene que tener una cola Monitor de errores donde cada
// thread encola sus errores!


    socket.BindAndListen(BACKLOG);

//    proteger a las DBs

    UsuariosDB users(usersFile);
    MateriasDB materias(materiasFile);
    Session session(socket, errorMonitor, users, materias);
    session.start();


    socket.Destroy();

    return 0;
}

int main(int argc, char **argv){
        server(argv[1], argv[2], argv[3]);

    return 0;
}
