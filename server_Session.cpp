#include <cstring>
#include <string>
#include <vector>
#include "server_Session.h"
#include "server_UserFactory.h"
//#include "server_Alumno.h"
#include "common_CommandParser.h"
#define BUFFSIZE 300
#define READ_SHTDWN 1
#define SERVER_MODE 0
#define LENGTH_SIZE 4
#define CLIENT_SHTDWN 0
#define CODE_POS 0

using std::cerr;

Session::Session(const Socket &socketServer) {
    Socket new_socket;
    socketServer.Accept(new_socket);
    socket = new_socket;
    user = nullptr;
}

void Session::receiveCommands(){
//    unsigned char buffer_leer[BUFFSIZE] = {0};
//    int read = 0;
    bool shutdown = false;
    while (!shutdown){
        string recv_command;
        try {

            recv_command = socket.ReceiveStrWLen(LENGTH_SIZE);
        } catch(std::exception& e){
//            TODO cambiar aca esto por la exc correcta
//            y volver a mandarla? depende si hay que mostrar esto en otros
// casos
            cerr << user->print() << " desconectado." << endl;
            shutdown = true;
            continue;
        }

//Aca viene la parte de devolver un vector de comandos.

        vector<string> commands;
        parser.parseCommand(recv_command, commands);
        cerr << user->print() << " ejecuta " << commands[CODE_POS] << "."  <<
                                                                           endl;
        string output = user->executeCommand(commands);
        cout << output << endl;
//        socket.Send((unsigned char *)&output[0], output.size());
    }
}

void Session::start() {

    string parameters = socket.ReceiveStrWLen(LENGTH_SIZE);

    vector<string> params;
    parser.parseUserInfo(parameters, params);


//    Aca llamo a la factory para que me cree el usuario que necesito, le
// paso un vector y que el se encargue de crear de acuerdo a eso.
    UserFactory factory;
    try {
        user = factory.createUser(params);
    } catch(std::invalid_argument& e){
//        user = nullptr;
        cerr << e.what() << endl;
        return;
    }

    cerr << user->print() << " conectado." << endl;

    receiveCommands();
}

Session::~Session() {
    if (user){ delete(user); }
//    socket.Shutdown(READ_SHTDWN);
    socket.accept_destroy();
}
