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

#define LENGTH_SIZE 4


int client(const char *ip, const char *port, vector<string> arguments){
    int status;
    CommandParser parser;
    Socket client_socket;
    status = client_socket.CreateAndConnect(ip, port);
    if (status < 0) { cout << "hubo un problema conecntando :/" <<endl; }

    string login = parser.delimitCommands(arguments);

//    TODO create ints of 4 bytes only.. que se yo
    client_socket.SendStrWLen(login, LENGTH_SIZE);

    string command;
    while (getline(std::cin, command)){
        string built_command = parser.buildCommand(command);

        client_socket.SendStrWLen(built_command, LENGTH_SIZE);
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
