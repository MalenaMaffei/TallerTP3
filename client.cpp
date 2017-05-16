#include "common_Socket.h"
#include <string>
#include <iostream>
#include "common_CommandParser.h"
#include "common_SocketException.h"
#include <deque>
using std::string;
using std::deque;
using std::cout;
using std::endl;
using std::cin;
#define LENGTH_SIZE 4


void client(string ip, string port, deque<string> arguments){
    CommandParser parser;
    Socket client_socket;
    try {
        client_socket.CreateAndConnect(ip, port);
    } catch(SocketException& e){
        cout << e.what() << endl;
        return;
    }

    string login = parser.delimitCommands(arguments);
//    TODO create ints of 4 bytes only.. que se yo
    try {
        client_socket.SendStrWLen(login, LENGTH_SIZE);
    } catch(SocketException& e) {
        cout << e.what() << endl;
        client_socket.Close();
        return;
    }

    string command;
    while (getline(std::cin, command)){
        try {
            string built_command = parser.buildCommand(command);
            client_socket.SendStrWLen(built_command, LENGTH_SIZE);
            string server_response = client_socket.ReceiveStrWLen(LENGTH_SIZE);
            cout << server_response;
        } catch(SocketException& e){
            cout << "Servidor offline." << endl;
            break;
        } catch(std::invalid_argument& e){
            cout << e.what() << endl;
            continue;
        }
    }

//    client_socket.Shutdown(SHUT_RDWR);
    client_socket.Close();
    return;
}

int main(int argc, char **argv){
    deque<string> arguments(argv + 3, argv + argc);
    client(argv[1], argv[2], arguments);

    return 0;
}
