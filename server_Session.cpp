#include "server_Session.h"
//#include <cstring>
#include <string>
//#include <vector>
#include "server_UserFactory.h"
#include "common_SocketException.h"
#include <deque>
//#include "common_CommandParser.h"
#define BUFFSIZE 300
#define READ_SHTDWN 1
#define SERVER_MODE 0
#define LENGTH_SIZE 4
#define CLIENT_SHTDWN 0
#define CODE_POS 0

using std::deque;

Session::Session(Socket newSocket, ErrorMonitor &errorMonitor, DB &database) :
    socket(newSocket), errorMonitor(errorMonitor), database(database){
    user = nullptr;
    exit = false;
}

void Session::receiveCommands(){
    while (!exit){
        string recv_command;
        try {
            recv_command = socket.ReceiveStrWLen(LENGTH_SIZE);
        } catch(SocketException& e){
            errorMonitor.outputError(user->print() + " desconectado.");
            shutdown();
            continue;
        }

//Aca viene la parte de devolver un vector de comandos.
        deque<string> commands;
        parser.parseCommand(recv_command, commands);
        errorMonitor.outputCommand(user->print(), commands[CODE_POS]);
        string output = user->executeCommand(commands);
        socket.SendStrWLen(output, LENGTH_SIZE);
    }
}

void Session::run() {
    string parameters;
    try {
        parameters = socket.ReceiveStrWLen(LENGTH_SIZE);
    } catch(SocketException& e) {
        return;
    }

    deque<string> params;
    parser.parseUserInfo(parameters, params);

    UserFactory factory;
    try {
        user = factory.createUser(params, database);
    } catch(std::invalid_argument& e){
        errorMonitor.outputError(e.what());
        shutdown();
        return;
    }
    errorMonitor.outputError(user->print() + " conectado.");

    receiveCommands();
}

Session::~Session() {
    if (user){
        delete(user);
    }
    socket.Close();
}

void Session::shutdown() {
    if (exit){
        return;
    }
    exit = true;
    socket.Shutdown(SHUT_RDWR);
}
