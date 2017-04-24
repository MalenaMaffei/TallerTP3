#include "common_Socket.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "common_CommandParser.h"
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

#define SEND_SHTDWN 0
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
    CommandParser parser;
    Socket client_socket;
    status = client_socket.CreateAndConnect(ip, port);
    if (status < 0) { cout << "hubo un problema conecntando :/" <<endl; }

//    std::for_each(arguments.begin(), arguments.end(), [](string &a){
//            std::cout << "argumento: " << a << std::endl;
//    });

//    send_message(client_socket, arguments);


    string message = build_message(arguments);
//    unsigned char* char_length;

//    TODO create ints of 4 bytes only
    int normal_length = message.size();
    int net_length = htonl(normal_length);
//    printf("int normal length: %i", normal_length);
//    printf("int net length: %i", net_length);
    client_socket.Send((unsigned char*)&net_length, LENGTH_SIZE);
    char *char_message = &message[0];
    client_socket.Send((unsigned char *)char_message, message.size());


//    hasta aca se mandaron los argumentos, ahora abro la entrada estandar
    string command;
    while (getline (std::cin, command)){

        string built_command = parser.buildCommand(command);

        normal_length = built_command.size();
        net_length = htonl(normal_length);
        client_socket.Send((unsigned char*)&net_length, LENGTH_SIZE);

        char_message = &built_command[0];
        client_socket.Send((unsigned char *)char_message, built_command.size());
        cout << "lo que pusiste: " << built_command << endl;
    }


    client_socket.Shutdown(SHUT_WR);
    client_socket.Destroy();
    return 0;
}

int main(int argc, char **argv){
    std::vector<std::string> arguments(argv + 3, argv + argc);
        client(argv[1], argv[2], arguments);

    return 0;
}
