#include "common_Socket.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using std::string;
using std::vector;

#define CLIENT_MODE 1
#define LENGTH_SIZE 4
string build_message(vector<string> arguments){
    string message;
    std::for_each(arguments.begin(), arguments.end(), [&](string a){
        message = message + a + "-";
    });
    message.pop_back();
    return message;

}

void send_message(Socket & socket, vector<string> arguments){
//    string message = build_message(arguments);
//    unsigned char* char_length;
//    int net_length = htonl(message.size() + LENGTH_SIZE);
//    char_length = (unsigned char*)&net_length;
//    socket.Send(char_length, LENGTH_SIZE);
//    char *char_message = &message[0];
//    socket.Send((unsigned char *)char_message, message.size());
}

int client(const char *ip, const char *port, vector<string> arguments){
    int status;

    Socket client_socket;
    status = client_socket.CreateAndConnect(ip, port);
    if (status < 0) { return 0; }

    std::for_each(arguments.begin(), arguments.end(), [](string &a){
            std::cout << "argumento: " << a << std::endl;
    });

//    send_message(client_socket, arguments);


    string message = build_message(arguments);
//    unsigned char* char_length;

//    TODO create ints of 4 bytes only
    int normal_length = message.size();
    int net_length = htonl(normal_length);
    printf("int normal length: %i", normal_length);
    printf("int net length: %i", net_length);
    client_socket.Send((unsigned char*)&net_length, LENGTH_SIZE);
    char *char_message = &message[0];
    client_socket.Send((unsigned char *)char_message, message.size());








//
//    string argumentos = build_message(arguments);
    std::cout << "msg created: " << message << std::endl;



//    int my_id = 1233;
//    int my_net_id = htonl(my_id);
//    send(sock, (const char*)&my_net_id, 4, 0);
//    string hola = "Hello world";
//    char *holaChar = &argumentos[0];
//    client_socket.Send((unsigned char *)holaChar, hola.length());
//
    client_socket.Shutdown(CLIENT_MODE);
//
//
//    Destroy(&client_socket);
    return 0;
}

int main(int argc, char **argv){

//        char *server_ip = argv[2];
//        char *server_port = argv[3];
//        char *file_name = argv[4];
    std::vector<std::string> arguments(argv + 3, argv + argc);
        client("127.0.0.1", "8080", arguments);

    return 0;
}