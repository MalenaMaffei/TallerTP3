#include <string>
#include <iostream>
#include "server_Server.h"
using std::string;

int main(int argc, char **argv){
    string server_port = argv[1];
    string usersFile = argv[2];
    string materiasFile = argv[3];

    Server server(server_port, usersFile, materiasFile);
    server.start();
    bool quit = false;
    string input;
    while (!quit){
        getline(std::cin, input);
        quit = input == "q";
    }
    server.shutdown();
    server.join();
    return 0;
}

