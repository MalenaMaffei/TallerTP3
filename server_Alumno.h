#ifndef TP2_ALUMNO_H
#define TP2_ALUMNO_H
#include "server_User.h"
#include <string>
//#include <vector>
#include <deque>
class Alumno : public User {
public:
    Alumno(DB &database, const string &id);

    virtual string listarInscripciones();
//    virtual string inscribir(std::deque<string> &args);
//    virtual string desinscribir(std::deque<string> &args);
    virtual string print() const;
  const string &getId() const;
 protected:
  Inscripcion createInscripcion(std::deque<string> &args);
  Desinscripcion createDesinscripcion(std::deque<string> &args);
  void sendTransaction(Transaction & transaction);

 private:
    string id;
};


#endif //TP2_ALUMNO_H
