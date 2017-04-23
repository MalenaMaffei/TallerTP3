#include <cstring>
#include "server_Session.h"
#include "server_UserFactory.h"
//#include "server_Alumno.h"
#define BUFFSIZE 300
#define READ_SHTDWN 1
#define SERVER_MODE 0
#define LENGTH_SIZE 4

Session::Session(const Socket &socketServer) {
    Socket new_socket;
    socketServer.Accept(new_socket);
    socket = new_socket;
}

void Session::start() {
    unsigned char buffer_leer[BUFFSIZE] = {0};
    int read = 0;
    while (read < LENGTH_SIZE){
        read = socket.Receive(buffer_leer,LENGTH_SIZE);
    }

//    casteo los 4 bytes en un int y lo doy vuelta
    int net_length;
    std::memcpy(&net_length, buffer_leer, sizeof net_length);

//    cout << "el int sacado sin pasarlo: " << net_length << endl;
    int normal_length = ntohl(net_length);
//    cout << "el int pasado: " << normal_length << endl;


    int bytes_read = 0;

//    TODO ir moviendo el puntero. podria hacer un receive string de X size...
    while (bytes_read < normal_length){
        bytes_read += socket.Receive(buffer_leer,BUFFSIZE);
    }
    buffer_leer[bytes_read] = '\0';

//    printf("%s\n", buffer_leer);

//TODO sacar esto de aca!
    string parameters((char *)buffer_leer);
    string delimiter = "-";
    vector<string> params;
    size_t pos = 0;
    std::string token;
    while ((pos = parameters.find(delimiter)) != std::string::npos) {
        token = parameters.substr(0, pos);
        std::cout << token << std::endl;
        params.push_back(token);
        parameters.erase(0, pos + delimiter.length());
    }
    params.push_back(parameters);
    std::cout << params.size() << std::endl;

//    Aca llamo a la factory para que me cree el usuario que necesito, le
// paso un vector y que el se encargue de crear de acuerdo a eso.
    UserFactory factory;
    user = factory.createUser(params);

    user->listarMaterias();
    user->desinscribir("1", "holitas");
    user->inscribir("1", "holitas");
    user->listarInscripciones();



}

Session::~Session() {
//Destruir usuario tambien
    delete(user);
    socket.Shutdown(READ_SHTDWN);

    socket.accept_destroy();
}
