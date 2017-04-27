#include <cstring>
#include <string>
#include <vector>
#include "server_Session.h"
#include "server_UserFactory.h"


#include "common_CommandParser.h"
#include "MateriasDB.h"
#define BUFFSIZE 300
#define READ_SHTDWN 1
#define SERVER_MODE 0
#define LENGTH_SIZE 4
#define CLIENT_SHTDWN 0
#define CODE_POS 0



Session::Session(const Socket &socketServer, ErrorMonitor &errorMonitor,
                 DB &database) :
    errorMonitor(errorMonitor), database(database) {
    Socket new_socket;
    socketServer.Accept(new_socket);
    socket = new_socket;
    user = nullptr;
}

void Session::receiveCommands(){
    bool shutdown = false;
    while (!shutdown){
        string recv_command;
        try {
            recv_command = socket.ReceiveStrWLen(LENGTH_SIZE);
        } catch(std::runtime_error& e){
//            TODO cambiar aca esto por la exc correcta
//            y volver a mandarla? depende si hay que mostrar esto en otros
// casos
            errorMonitor.outputError(user->print() + " desconectado.");
            shutdown = true;
            continue;
        }

//Aca viene la parte de devolver un vector de comandos.
        vector<string> commands;
        parser.parseCommand(recv_command, commands);
        errorMonitor.outputError(user->print() + " ejecuta " +
            commands[CODE_POS] + ".");
        string output = user->executeCommand(commands);
        socket.SendStrWLen(output, LENGTH_SIZE);
    }
}

void Session::start() {
    string parameters = socket.ReceiveStrWLen(LENGTH_SIZE);

    vector<string> params;
    parser.parseUserInfo(parameters, params);

    UserFactory factory;
    try {
        user = factory.createUser(params, database);
    } catch(std::invalid_argument& e){
        errorMonitor.outputError(e.what());
        return;
    }
    errorMonitor.outputError(user->print() + " conectado.");

    receiveCommands();
}

Session::~Session() {
    if (user){ delete(user); }
//    socket.Shutdown(READ_SHTDWN);
    socket.accept_destroy();
}
