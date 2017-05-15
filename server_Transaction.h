#ifndef TP2_TRANSACTION_H
#define TP2_TRANSACTION_H
#include "server_DBException.h"
#include <string>
#include <map>
using std::string;
class Transaction {
 public:
  Transaction(const string &materia,const string &curso,const string &alumnoId);
  const string &getMateria() const;
  const string &getCurso() const;
  const string &getId() const;
  const string &getAlumnoId() const;

  virtual void updateInscriptions(std::map<string, string> &materiaInfo) const
  {}

 protected:
  string materia;
  string curso;
  string id;
  string alumnoId;
};

#endif //TP2_TRANSACTION_H
