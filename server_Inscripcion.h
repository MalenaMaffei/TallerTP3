#ifndef TP2_INSCRIPCION_H
#define TP2_INSCRIPCION_H
#include "server_Transaction.h"
#include <string>
class Inscripcion : public Transaction{
 public:
  Inscripcion(const string &materia,const string &curso,
              const string &alumnoId);

  void updateInscriptions(string &inscriptos, string &inscripciones,
                            string &vacancies) const;
};

#endif //TP2_INSCRIPCION_H
