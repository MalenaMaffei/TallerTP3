#ifndef TP2_SESSION_H
#define TP2_SESSION_H

#include "common_Socket.h"
#include "server_User.h"

class Session {
public:
    explicit Session(const Socket &socketServer);
    void start();

    virtual ~Session();

private:
//    tambien deberia tener una fabrica que le crea los usuarios
    Socket socket;
    User* user;

    void receiveCommands();
};


#endif //TP2_SESSION_H
