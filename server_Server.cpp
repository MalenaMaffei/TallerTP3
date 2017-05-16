#include "server_Server.h"
//#include "common_Socket.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "server_Session.h"
#include "server_DB.h"
#include "common_SocketException.h"
#define BACKLOG 10
#define BUFFSIZE 300
#define SERVER_MODE 0
#define LENGTH_SIZE 4

using std::cout;
using std::endl;

Server::Server(const string &port,const string &usuariosFile,
               const string &materiasFile)
    : port(port), usuariosFile(usuariosFile), materiasFile(materiasFile) {
    exit = false;
}

void Server::run(){
    acceptSocket.Create("", port, SERVER_MODE);

    try{
        acceptSocket.BindAndListen(BACKLOG);
    } catch(SocketException& e){
        cout << e.what() << endl;
        return;
    }

    ErrorMonitor errorMonitor;
    DB database(usuariosFile, materiasFile);

    std::vector<Session*> sessions;
    while (!exit){
        try {
            Socket newSocket = acceptSocket.Accept();
            Session *session = new Session(newSocket, errorMonitor, database);
            sessions.push_back(session);
            session->start();
        } catch(SocketException& e){ continue; }
    }

    std::for_each(sessions.begin(), sessions.end(), [](Session* session){
      session->shutdown();
      session->join();
      delete session;
    });

    return;
}

void Server::shutdown() {
    exit = true;
    acceptSocket.Shutdown(SHUT_RDWR);
}

Server::~Server() {
    acceptSocket.Close();
}


