#ifndef TP2_DOCENTE_H
#define TP2_DOCENTE_H

#include "server_User.h"
#include <string>
#include <deque>
class Docente : public User  {
public:
    Docente(DB &database, const string &id);

    virtual string listarInscripciones();
    virtual string print() const;
    const string &getId() const;
    bool hasPermissions(std::string materia);
 protected:
    void createInscripcion(std::deque<string> &args);
    void createDesinscripcion(std::deque<string> &args);

 private:
    string id;
};


#endif //TP2_DOCENTE_H
