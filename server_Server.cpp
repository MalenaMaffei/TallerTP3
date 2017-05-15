#include "server_Server.h"
//#include "common_Socket.h"
#include <string>
//#include <cstring>
//#include <regex>
#include <vector>
//#include "server_User.h"
//#include "server_Admin.h"
//#include "server_Docente.h"
//#include "server_Alumno.h"
#include <iostream>
#include "server_Session.h"
#include "server_DB.h"
#include "common_InputGetter.h"
//#include "common_InputQueueMonitor.h"
#include "common_SocketException.h"
#define BACKLOG 10
#define BUFFSIZE 300
#define READ_SHTDWN 1
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
//    ErrorMonitor errorMonitor;
////    InputQueueMonitor queueMonitor;
//
//    Socket socketServer;
//
    acceptSocket.Create(0, port.c_str(), SERVER_MODE);
//
    try{
        acceptSocket.BindAndListen(BACKLOG);
    } catch(SocketException& e){
        cout << e.what() << endl;
//        acceptSocket.Destroy();
        return;
    }
//
//    socketServer.setToNonBlocking();
//
//    DB database(usuariosFile, materiasFile);
//
//    std::vector<Session*> sessions;
////    Thread *getter = new InputGetter(queueMonitor);
////    getter->start();
//
//    while (! exit){
////        Socket new_socket;
//        try {
//            int new_fd = socketServer.Accept();
//            Session *session =
//                new Session(new_fd, errorMonitor, database);
//            sessions.push_back(session);
//            session->start();
//        } catch(SocketException& e){ continue; }
//    }
//
////    TODO avisar a los threads que se va a desconectar
////    getter->join();
////    delete getter;
//
//
////    TODO cabiar por un foreach
//    for (size_t i = 0; i < sessions.size(); ++i) {
//        sessions[i]->join();
//        delete sessions[i];
//    }

    ErrorMonitor errorMonitor;
    DB database(usuariosFile, materiasFile);

    std::vector<Session*> sessions;
    while (!exit){
        try {
//            int new_fd = acceptSocket.Accept();
//            Session *session = new Session(new_fd, errorMonitor, database);
            Socket newSocket = acceptSocket.Accept();
            Session *session = new Session(newSocket, errorMonitor, database);
            sessions.push_back(session);
            session->start();
        } catch(SocketException& e){ continue; }
    }
////    TODO cabiar por un foreach
    for (size_t i = 0; i < sessions.size(); ++i) {
        sessions[i]->shutdown();
        sessions[i]->join();
        delete sessions[i];
    }
    return;
}

void Server::shutdown() {
    exit = true;
//    acceptSocket.Destroy();
    acceptSocket.Shutdown(SHUT_RDWR);
}

Server::~Server() {
    acceptSocket.Destroy();
}


