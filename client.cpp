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
    try {
        client_socket.SendStrWLen(login, LENGTH_SIZE);
    } catch(std::exception& e) {
        cout << e.what() << endl;
        client_socket.Shutdown(SHUT_WR);
        client_socket.Destroy();
        return 0;
    }
//    cout << "is connected before input?: " << client_socket.isConnected() <<
//                                                                          endl;


    string command;
//    NOTE esta bien hacer asi con un break? yo supongo que si, si hay tiempo
//    hacer otro thread que chequee la entrada estandar
//    Me fijo todo el tiempo si estoy conectado en este loop, si encuentro
// algo en la cola de comandos, lo envio, sino sigo chequeando la conextion,
// en la cola de comandos tengo que poder senialar que ya se llego al fin de
// los comandos o ver como darme cuenta si el thread termino de correr. El
// thread de comandos lee stdin todo el dia y va  encolando los comandos.
    while (getline(std::cin, command)){
        try {
        string built_command = parser.buildCommand(command);

        client_socket.SendStrWLen(built_command, LENGTH_SIZE);
//        cout << "lo que pusiste: " << built_command << endl;

            string server_response = client_socket.ReceiveStrWLen(LENGTH_SIZE);
            cout << server_response;
        } catch(std::exception& e){ break; }
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
