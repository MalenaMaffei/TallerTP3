#include "common_Socket.h"
#include <string>
#include <vector>
// #include <algorithm>
#include <iostream>
#include "common_CommandParser.h"
#include "common_SocketException.h"
#include "common_InputQueueMonitor.h"
#include "common_InputGetter.h"
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;
#define LENGTH_SIZE 4


void client(const char *ip, const char *port, vector<string> arguments){
    CommandParser parser;
    Socket client_socket;
    try {
        client_socket.CreateAndConnect(ip, port);
    } catch(SocketException& e){
        cout << e.what() << endl;
        return;
    }

//    string command;
//    while (getline(cin,command)){
//        cout << command << endl;
//    }

    string login = parser.delimitCommands(arguments);
//    TODO create ints of 4 bytes only.. que se yo
    try {
        client_socket.SendStrWLen(login, LENGTH_SIZE);
    } catch(SocketException& e) {
        cout << e.what() << endl;
        client_socket.Destroy();
        return;
    }

    string command;
    while (getline(std::cin, command)){
        string built_command = parser.buildCommand(command);
        try {
            client_socket.SendStrWLen(built_command, LENGTH_SIZE);
        } catch(SocketException& e){
            break;
        }
        try {
            string server_response = client_socket.ReceiveStrWLen(LENGTH_SIZE);
            cout << server_response;
        } catch(SocketException& e){
            break;
        }
    }


    client_socket.Shutdown(SHUT_RDWR);
    client_socket.Destroy();
    return;
}

int main(int argc, char **argv){
    std::vector<std::string> arguments(argv + 3, argv + argc);
        client(argv[1], argv[2], arguments);

    return 0;
}
