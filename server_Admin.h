#ifndef TP2_SERVER_ADMIN_H
#define TP2_SERVER_ADMIN_H
#include "server_User.h"
#include <string>
//#include <vector>
#include <deque>
class Admin : public User {
public:
    explicit Admin(DB &database);
    virtual string listarInscripciones();
//    virtual string inscribir(std::deque<string> &args);
//    virtual string desinscribir(std::deque<string> &args);
    virtual string print() const;
 protected:
    Inscripcion createInscripcion(std::deque<string> &args);
    Desinscripcion createDesinscripcion(std::deque<string> &args);
    void sendTransaction(Transaction & transaction);
};


#endif //TP2_SERVER_ADMIN_H
