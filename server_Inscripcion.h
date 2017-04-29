//
// Created by male on 29/04/17.
//

#ifndef TP2_INSCRIPCION_H
#define TP2_INSCRIPCION_H
#include "server_Transaction.h"
class Inscripcion : public Transaction{
 public:
  Inscripcion(const string &materia,const string &curso,
              const string &alumnoId);

  void updateInscriptions(string &inscriptos, string &inscripciones)const;
  void updateVacancies(string &vacancy) const;
};

#endif //TP2_INSCRIPCION_H
