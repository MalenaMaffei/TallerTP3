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


int server(const char *server_port){
    Socket socket;
    socket.Create(0, server_port, SERVER_MODE);

//    cout << "creando un admin:"<<endl;
//    Admin admin;
//    admin.listarInscripciones();
//    admin.inscribir("1", "algo");
//    admin.desinscribir("1", "algo");
//
//    cout << "creadno un alumno: "<<endl;
//    Alumno alumno;
//    alumno.listarInscripciones();
//    alumno.inscribir("1", "algo");
//    alumno.desinscribir("1", "algo");
//
//    cout << "creadno un docente: "<<endl;
//    Docente docente;
//    docente.listarInscripciones();
//    docente.inscribir("1", "algo");
//    docente.desinscribir("1", "algo");

    socket.BindAndListen(BACKLOG);

    cout << "bind and listen" << endl;


    Session session(socket);
    session.start();

//    Socket new_socket;
//    socket.Accept(new_socket);

//    cout << "socket accept creado" << endl;

//aca es cuando le paso el socket a la sesion


//    unsigned char buffer_leer[BUFFSIZE] = {0};
//    int read = 0;
//    while (read < LENGTH_SIZE){
//        read = new_socket.Receive(buffer_leer,LENGTH_SIZE);
//    }
//
////    casteo los 4 bytes en un int y lo doy vuelta
//    int net_length;
//    std::memcpy(&net_length, buffer_leer, sizeof net_length);
//
//    cout << "el int sacado sin pasarlo: " << net_length << endl;
//    int normal_length = ntohl(net_length);
//    cout << "el int pasado: " << normal_length << endl;
//
//
//    int bytes_read = 0;
//
////    TODO ir moviendo el puntero. podria hacer un receive string de X size...
//    while (bytes_read < normal_length){
//        bytes_read += new_socket.Receive(buffer_leer,BUFFSIZE);
//    }
//    buffer_leer[bytes_read] = '\0';
//
//    printf("%s\n", buffer_leer);
//
//
//    string parameters((char *)buffer_leer);
//    std::string delimiter = "-";
//
//    size_t pos = 0;
//    std::string token;
//    while ((pos = parameters.find(delimiter)) != std::string::npos) {
//        token = parameters.substr(0, pos);
//        std::cout << token << std::endl;
//        parameters.erase(0, pos + delimiter.length());
//    }
//    std::cout << parameters << std::endl;



//
//    new_socket.Shutdown(READ_SHTDWN);
//
//    new_socket.accept_destroy();






    socket.Destroy();

//    accept_destroy(&new_socket);
//    Destroy(&socket);

    return 0;
}

int main(int argc, char **argv){

        server("8080");

    return 0;
}