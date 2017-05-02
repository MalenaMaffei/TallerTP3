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

#define LENGTH_SIZE 4


int client(const char *ip, const char *port, vector<string> arguments){
    CommandParser parser;
    Socket client_socket;
    try {
        client_socket.CreateAndConnect(ip, port);
    } catch(SocketException& e){
        cout << e.what() << endl;
        return 0;
    }

    client_socket.CreateAndConnect(ip, port);

    string login = parser.delimitCommands(arguments);

//    TODO create ints of 4 bytes only.. que se yo
    try {
        client_socket.SendStrWLen(login, LENGTH_SIZE);
    } catch(SocketException& e) {
        cout << e.what() << endl;
        client_socket.Destroy();
        return 0;
    }


    string command;

//    while (getline(std::cin, command)){
//        try {
//            string built_command = parser.buildCommand(command);
////            cout << built_command << endl;
//            client_socket.SendStrWLen(built_command, LENGTH_SIZE);
//            string server_response = client_socket.ReceiveStrWLen(LENGTH_SIZE);
//            cout << server_response;
//        } catch(SocketException& e){ break; }
//    }

    InputQueueMonitor queueMonitor;
    Thread *getter = new InputGetter(queueMonitor);
    getter->start();

//    cout << client_socket.isConnected() << endl;
//    while (! queueMonitor.isQuittingTime() && client_socket.isConnected()){
    while (!queueMonitor.isQuittingTime() || !queueMonitor.isEmpty()){
        if (queueMonitor.isEmpty()){
//            cout << "estaba vacio y segui" << endl;
            continue; }

        string built_command = parser.buildCommand(queueMonitor.pop());
//        cout << built_command << endl;
//        cout << "is empty now?: " << queueMonitor.isEmpty() << endl;
        try {
            client_socket.SendStrWLen(built_command, LENGTH_SIZE);
           string server_response = client_socket.ReceiveStrWLen(LENGTH_SIZE);
            cout << server_response;
        } catch(SocketException& e){ break; }
    }

    getter->join();
    delete getter;

cout << "no lo estoy cerrando?" << endl;
//    client_socket.Shutdown(SHUT_WR);
    client_socket.Destroy();
    cout << "en teoria ya esta" << endl;
    return 0;
}

int main(int argc, char **argv){
    std::vector<std::string> arguments(argv + 3, argv + argc);
        client(argv[1], argv[2], arguments);

    return 0;
}
