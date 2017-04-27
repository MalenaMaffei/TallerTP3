#ifndef TP2_SESSION_H
#define TP2_SESSION_H

#include "common_Socket.h"
#include "server_User.h"
#include "common_CommandParser.h"
#include "server_ErrorMonitor.h"
#include "UsuariosDB.h"
#include "MateriasDB.h"

class Session {
public:
    explicit Session(const Socket &socketServer,ErrorMonitor &errorMonitor,
                         DB &database);
    void start();

    virtual ~Session();

private:
    Socket socket;
    User* user;
    CommandParser parser;
    ErrorMonitor &errorMonitor;
    DB &database;
//    UsuariosDB &usersDB;
//    MateriasDB &materiasDB;
    void receiveCommands();
};


#endif //TP2_SESSION_H
