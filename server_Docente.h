#ifndef TP2_DOCENTE_H
#define TP2_DOCENTE_H

#include "server_User.h"
#include <string>
//#include <vector>
#include <deque>
class Docente : public User  {
public:
    Docente(DB &database, const string &id);

    virtual string listarInscripciones();
//    string inscribir(std::deque<string> &args);
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


#endif //TP2_DOCENTE_H
