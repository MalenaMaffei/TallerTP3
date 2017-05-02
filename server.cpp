#include "common_Socket.h"
#include <string>
//#include <cstring>
//#include <regex>
#include <vector>
//#include "server_User.h"
//#include "server_Admin.h"
//#include "server_Docente.h"
//#include "server_Alumno.h"
#include <iostream>
#include "server_Session.h"
#include "server_DB.h"
#include "common_InputGetter.h"
#include "common_InputQueueMonitor.h"
#include "common_SocketException.h"
#define BACKLOG 10
#define BUFFSIZE 300
#define READ_SHTDWN 1
#define SERVER_MODE 0
#define LENGTH_SIZE 4

using std::cout;
using std::endl;

int server(const char *server_port, string usersFile, string materiasFile){
    ErrorMonitor errorMonitor;
    InputQueueMonitor queueMonitor;

    Socket socketServer;

    socketServer.Create(0, server_port, SERVER_MODE);

    try{
        socketServer.BindAndListen(BACKLOG);
    } catch(std::runtime_error& e){
        cout << e.what() << endl;
        socketServer.Destroy();
        return 0;
    }

    socketServer.setToNonBlocking();

    DB database(usersFile, materiasFile);

    std::vector<Session*> sessions;
    Thread *getter = new InputGetter(queueMonitor);
    getter->start();

    while (! queueMonitor.isQuittingTime()){
        Socket new_socket;
        try {
            new_socket = socketServer.Accept();
        } catch(SocketException& e){ continue; }

        Session *session =
            new Session(new_socket, errorMonitor, database, queueMonitor);
        sessions.push_back(session);
        session->start();
    }

//    TODO avisar a los threads que se va a desconectar
    getter->join();
    delete getter;

//    TODO cabiar por un foreach
    for (size_t i = 0; i < sessions.size(); ++i) {
        sessions[i]->join();
        delete sessions[i];
    }

    socketServer.Destroy();

    return 0;
}

int main(int argc, char **argv){
        server(argv[1], argv[2], argv[3]);

    return 0;
}
