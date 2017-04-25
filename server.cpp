#include "common_Socket.h"
#include <string>
#include <cstring>
#include "server_User.h"
#include "server_Admin.h"
#include "server_Docente.h"
#include "server_Alumno.h"
#include "server_Session.h"

#define BACKLOG 10
#define BUFFSIZE 300
#define READ_SHTDWN 1
#define SERVER_MODE 0
#define LENGTH_SIZE 4


int server(const char *server_port, string usersFile, string materiasFile){
    ErrorMonitor errorMonitor;
    Socket socket;
    socket.Create(0, server_port, SERVER_MODE);

//  TODO el server tiene que tener una cola Monitor de errores donde cada
// thread encola sus errores!

    socket.BindAndListen(BACKLOG);

//    proteger a las DBs

    UsuariosDB users(usersFile);

    Session session(socket, errorMonitor,
                    users);
    session.start();


    socket.Destroy();

    return 0;
}

int main(int argc, char **argv){
        server(argv[1], argv[2], argv[3]);

    return 0;
}
