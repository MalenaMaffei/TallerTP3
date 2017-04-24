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
    unsigned char buffer_leer[BUFFSIZE] = {0};
    int read = 0;
    bool shutdown = false;
    while (!shutdown){
        try {
            read = 0;
            while (read < LENGTH_SIZE){
                read = socket.Receive(buffer_leer,LENGTH_SIZE);
            }

            int net_length;
            std::memcpy(&net_length, buffer_leer, sizeof net_length);

            int normal_length = ntohl(net_length);
            int bytes_read = 0;

//    TODO ir moviendo el puntero. podria hacer un receive string de X size...
            while (bytes_read < normal_length){
                bytes_read += socket.Receive(buffer_leer,BUFFSIZE);
            }
            buffer_leer[bytes_read] = '\0';
        } catch(std::exception& e){
//            TODO cambiar aca esto por la exc correcta
            cerr << user->print() << " desconectado." << endl;
            shutdown = true;
            continue;
        }

//Aca viene la parte de devolver un vector de comandos.
        string recv_command((char *)buffer_leer);
        vector<string> commands;
        parser.parseCommand(recv_command, commands);
        cerr << user->print() << " ejecuta " << commands[CODE_POS] << "."  <<
                                                                           endl;
//        aca tengo que pasarle al user el vector de comandos
        string output = user->executeCommand(commands);
        cout << output << endl;
    }
}

void Session::start() {
//    CommandParser parser;
    unsigned char buffer_leer[BUFFSIZE] = {0};
    int read = 0;
    while (read < LENGTH_SIZE){
        read = socket.Receive(buffer_leer,LENGTH_SIZE);
    }

//    casteo los 4 bytes en un int y lo doy vuelta
    int net_length;
    std::memcpy(&net_length, buffer_leer, sizeof net_length);
    int normal_length = ntohl(net_length);

    int bytes_read = 0;
//    TODO ir moviendo el puntero. podria hacer un receive string de X size...
    while (bytes_read < normal_length){
        bytes_read += socket.Receive(buffer_leer,BUFFSIZE);
    }
    buffer_leer[bytes_read] = '\0';


    string parameters((char *)buffer_leer);

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
    user->listarMaterias();
    user->desinscribir(vector<string>());
    user->inscribir(vector<string>());
    user->listarInscripciones();

    receiveCommands();
}

Session::~Session() {
//Destruir usuario tambien
    if (user){ delete(user); }

//    socket.Shutdown(READ_SHTDWN);

    socket.accept_destroy();
}
