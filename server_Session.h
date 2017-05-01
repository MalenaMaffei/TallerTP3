#ifndef TP2_SESSION_H
#define TP2_SESSION_H
#include "common_Thread.h"
#include "common_Socket.h"
#include "server_User.h"
#include "common_CommandParser.h"
#include "server_ErrorMonitor.h"
#include "common_InputQueueMonitor.h"

class Session : public Thread  {
public:
    explicit Session(Socket newSocket,
                         ErrorMonitor &errorMonitor,
                         DB &database,
                         InputQueueMonitor &input);
    void run();
    virtual ~Session();

private:
    Socket socket;
    User* user;
    CommandParser parser;
    ErrorMonitor &errorMonitor;
    DB &database;
    InputQueueMonitor &input;
    void receiveCommands();
};


#endif //TP2_SESSION_H
