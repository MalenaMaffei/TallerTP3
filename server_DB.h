#ifndef INC_3TP_DB_H
#define INC_3TP_DB_H
#include <string>
#include <map>
#include <vector>
#include "server_User.h"
#include "server_Docente.h"
#include "server_Transaction.h"
using std::map;
using std::string;
using std::vector;


class DB {
 public:
  DB(string usuariosFile, string materiasFile);
  string fillAllMaterias(string format);
  string fillNameById(string format);
  void validateUser(string userType, string id);
  bool materiaExists(string materia) const;
  void processTransaction(Transaction &transaction, Docente &user);
  void processTransaction(Transaction &transaction, User &user);
  void validateDocente(Transaction &transaction, string docenteId);

 private:
  void fillMaterias(string materiasFile);
  void fillUsuarios(string line);
  void validateMateria(string materia, string curso);
  void validateTransaction(Transaction transaction);

  std::map<string,map<string, string>> users;
  map<string,map<string, string>> materias;
};


#endif //INC_3TP_DB_H
