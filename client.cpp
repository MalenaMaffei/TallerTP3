#include "common_Socket.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

#define CLIENT_MODE 1

int client(const char *ip, const char *port, vector<string> params){
    int status;

    Socket client_socket;
    status = client_socket.CreateAndConnect(ip, port);
    if (status < 0) { return 0; }

//    string hola = "Hello world";
    char *holaChar = &saludo[0];
    client_socket.Send((unsigned char *)holaChar, saludo.length());

    client_socket.Shutdown(CLIENT_MODE);
//
//    recv_and_print(&client_socket);
//
//    socket_destroy(&client_socket);
    return 0;
}

int main(int argc, char **argv){

//        char *server_ip = argv[2];
//        char *server_port = argv[3];
//        char *file_name = argv[4];
    
        client("127.0.0.1", "8080", );

    return 0;
}