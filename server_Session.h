#ifndef TP2_SESSION_H
#define TP2_SESSION_H

#include "common_Socket.h"
#include "server_User.h"
#include "common_CommandParser.h"
#include "server_ErrorMonitor.h"

class Session {
public:
    explicit Session(const Socket &socketServer, ErrorMonitor errorMonitor);
    void start();

    virtual ~Session();

private:
//    tambien deberia tener una fabrica que le crea los usuarios
    Socket socket;
    User* user;
    CommandParser parser;
    ErrorMonitor errorMonitor;
    void receiveCommands();
};


#endif //TP2_SESSION_H
