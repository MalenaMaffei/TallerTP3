#ifndef TP2_SESSION_H
#define TP2_SESSION_H
#include "common_Thread.h"
#include "common_Socket.h"
#include "server_User.h"
#include "common_CommandParser.h"
#include "server_ErrorMonitor.h"
// TODO ver si al final esto vale la pena 
#include "common_InputQueueMonitor.h"

class Session : public Thread  {
public:
    explicit Session(int newFD,
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
