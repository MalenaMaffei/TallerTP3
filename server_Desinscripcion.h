//
// Created by male on 29/04/17.
//

#ifndef TP2_DESINSCRIPCION_H
#define TP2_DESINSCRIPCION_H
#include "server_Transaction.h"

class Desinscripcion : public Transaction {
 public:
  Desinscripcion(const string &materia,const string &curso,
                 const string &alumnoId);

  void updateInscriptions(string &inscriptos, string &inscripciones,
                            string &vacancies) const;
  void updateVacancies(string &vacancy) const;
};

#endif //TP2_DESINSCRIPCION_H
