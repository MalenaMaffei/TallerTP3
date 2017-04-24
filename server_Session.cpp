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

Session::Session(const Socket &socketServer) {
    Socket new_socket;
    socketServer.Accept(new_socket);
    socket = new_socket;
}

void Session::receiveCommands(){
    unsigned char buffer_leer[BUFFSIZE] = {0};
    int read = 0;
    while (true){
//        TODO METER TRY CATCHES POR ACA
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
//            printf("comando: %s", buffer_leer);
        } catch (std::exception& e){
//            TODO cambiar aca esto por la exc correcta
            std::cerr << user->print() << " desconectado." << std::endl;
            break;
        }
    }
//    read = socket.Receive(buffer_leer,LENGTH_SIZE);
//    cout << "ultimo read: "<<  read << endl;
}

void Session::start() {
    CommandParser parser;
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

//    printf("%s\n", buffer_leer);

//TODO sacar esto de aca!
    string parameters((char *)buffer_leer);

    vector<string> params;
    parser.parseUserInfo(parameters, params);


//    Aca llamo a la factory para que me cree el usuario que necesito, le
// paso un vector y que el se encargue de crear de acuerdo a eso.
    UserFactory factory;
    user = factory.createUser(params);
//
    user->listarMaterias();
    user->desinscribir("1", "holitas");
    user->inscribir("1", "holitas");
    user->listarInscripciones();
//
//    read = 0;
//    while (read < LENGTH_SIZE){
//        read = socket.Receive(buffer_leer,LENGTH_SIZE);
//    }
//
////    casteo los 4 bytes en un int y lo doy vuelta
//    std::memcpy(&net_length, buffer_leer, sizeof net_length);
//    normal_length = ntohl(net_length);
//
//    bytes_read = 0;
////    TODO ir moviendo el puntero. podria hacer un receive string de X size...
//    while (bytes_read < normal_length){
//        bytes_read += socket.Receive(buffer_leer,BUFFSIZE);
//    }
//    buffer_leer[bytes_read] = '\0';
//
//    printf("%s\n", buffer_leer);
//
//    read = 0;
//    while (read < LENGTH_SIZE){
//        read = socket.Receive(buffer_leer,LENGTH_SIZE);
//    }
//
////    casteo los 4 bytes en un int y lo doy vuelta
//    std::memcpy(&net_length, buffer_leer, sizeof net_length);
//    normal_length = ntohl(net_length);
//
//    bytes_read = 0;
////    TODO ir moviendo el puntero. podria hacer un receive string de X size...
//    while (bytes_read < normal_length){
//        bytes_read += socket.Receive(buffer_leer,BUFFSIZE);
//    }
//    buffer_leer[bytes_read] = '\0';
//
//    printf("%s\n", buffer_leer);
//
//    read = socket.Receive(buffer_leer,LENGTH_SIZE);
//    cout << "ultima vez que lee: " << read << endl;

    receiveCommands();
    cout << "holita" << endl;
}

Session::~Session() {
//Destruir usuario tambien
    delete(user);
//    socket.Shutdown(READ_SHTDWN);

    socket.accept_destroy();
}
