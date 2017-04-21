
#include "common_Socket.h"
#include <string>

using std::string;


#define R_BUFFSIZE 300
#define E_BUFFSIZE 100
#define OUTPUTMAX 200
#define CLIENT_MODE 1

int client(const char *ip, const char *port, const char *file){
    int status;

    Socket client_socket;
    status = client_socket.CreateAndConnect(ip, port);
    if (status < 0) { return 0; }

    string hola = "Hello world";
    char *holaChar = &hola[0];
    client_socket.Send((unsigned char *)holaChar, hola.length());

//    client_socket.Shutdown(1);
//
//    recv_and_print(&client_socket);
//
//    socket_destroy(&client_socket);
    return 0;
}