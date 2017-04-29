#ifndef TP2_ALUMNO_H
#define TP2_ALUMNO_H
#include "server_User.h"
#include <string>
#include <vector>
class Alumno : public User {
public:
    Alumno(DB &database, const string &id);

    virtual string listarInscripciones() const;
    virtual string inscribir(vector<string> &args) ;
    virtual string desinscribir(vector<string> &args);
    virtual string print() const;
  const string &getId() const;

 private:
    string id;
};


#endif //TP2_ALUMNO_H
