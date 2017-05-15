#ifndef TP2_ALUMNO_H
#define TP2_ALUMNO_H
#include "server_User.h"
#include <string>
#include <deque>

class Alumno : public User {
public:
    Alumno(DB &database, const string &id);

    virtual string listarInscripciones();
    virtual string print() const;
  const string &getId() const;
 protected:
  void createInscripcion(std::deque<string> &args);
  void createDesinscripcion(std::deque<string> &args);

 private:
    string id;
};

#endif //TP2_ALUMNO_H
