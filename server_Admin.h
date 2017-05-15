#ifndef TP2_SERVER_ADMIN_H
#define TP2_SERVER_ADMIN_H
#include "server_User.h"
#include <string>
#include <deque>

class Admin : public User {
public:
    explicit Admin(DB &database);
    virtual string listarInscripciones();
    virtual string print() const;
 protected:
    void createInscripcion(std::deque<string> &args);
    void createDesinscripcion(std::deque<string> &args);
};


#endif //TP2_SERVER_ADMIN_H
