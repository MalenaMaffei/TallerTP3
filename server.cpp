#include "common_Socket.h"
#include <string>


#define BACKLOG 10
#define BUFFSIZE 300
#define READ_SHTDWN 1
#define SERVER_MODE 0


int server(const char *server_port){
    Socket socket;
    socket.Create(0, server_port, SERVER_MODE);

    socket.BindAndListen(BACKLOG);

    Socket new_socket;
    socket.Accept(new_socket);


    unsigned char buffer_leer[BUFFSIZE] = {0};
    int read = 1;
    while (read>0){
        read = new_socket.Receive(buffer_leer,BUFFSIZE);
    }


    printf("%s\n", buffer_leer);

    new_socket.Shutdown(READ_SHTDWN);

//    socket_accept_destroy(&new_socket);
//    socket_destroy(&socket);

    return 0;
}

int main(int argc, char **argv){

        server("8080");

    return 0;
}