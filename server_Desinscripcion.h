#ifndef TP2_DESINSCRIPCION_H
#define TP2_DESINSCRIPCION_H
#include "server_Transaction.h"
#include <string>
#include <map>
class Desinscripcion : public Transaction {
 public:
  Desinscripcion(const string &materia,const string &curso,
                 const string &alumnoId);

  void updateInscriptions(std::map<string, string> &materiaInfo) const;
};

#endif //TP2_DESINSCRIPCION_H
