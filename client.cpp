#include "common_Socket.h"
#include <string>

using std::string;

#define CLIENT_MODE 1

int client(const char *ip, const char *port){
    int status;

    Socket client_socket;
    status = client_socket.CreateAndConnect(ip, port);
    if (status < 0) { return 0; }

    string hola = "Hello world";
    char *holaChar = &hola[0];
    client_socket.Send((unsigned char *)holaChar, hola.length());

    client_socket.Shutdown(CLIENT_MODE);
//
//    recv_and_print(&client_socket);
//
//    socket_destroy(&client_socket);
    return 0;
}

int main(){

//        char *server_ip = argv[2];
//        char *server_port = argv[3];
//        char *file_name = argv[4];
        client("127.0.0.1", "8080");

    return 0;
}