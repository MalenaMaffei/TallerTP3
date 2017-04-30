#ifndef TP2_DESINSCRIPCION_H
#define TP2_DESINSCRIPCION_H
#include "server_Transaction.h"
#include <string>
class Desinscripcion : public Transaction {
 public:
  Desinscripcion(const string &materia,const string &curso,
                 const string &alumnoId);

  void updateInscriptions(string &inscriptos, string &inscripciones,
                            string &vacancies) const;
};

#endif //TP2_DESINSCRIPCION_H
