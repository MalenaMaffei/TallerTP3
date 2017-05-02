#ifndef INC_3TP_DB_H
#define INC_3TP_DB_H
#include <string>
#include <map>
//#include <vector>
//#include "server_User.h"
#include "server_Docente.h"
#include "server_Transaction.h"
#include "server_Alumno.h"
#include "server_Admin.h"
#include <mutex>
using std::map;
using std::string;
using std::vector;


class DB {
 public:
  DB(string usuariosFile, string materiasFile);
  string fillAllMaterias(string format);
  string fillNameById(string format);

  string listarMateriasCabecera(string format, Docente &user);
  string listarMateriasCabecera(string format, Alumno &user);
  string listarMateriasCabecera(string format, Admin &user);
  void processTransaction(Transaction &transaction, Docente &user);
  void processTransaction(Transaction &transaction, User &user);
  void validateUser(string userType, string id);

 private:
  bool materiaExists(string materia) const;
  void validateDocente(Transaction &transaction, string docenteId);
  void acceptTransaction(Transaction &transaction);
  void fillMaterias(string materiasFile);
  void fillUsuarios(string line);
  void validateMateria(string materia, string curso);
  void validateTransaction(Transaction transaction);

  std::map<string,map<string, string>> users;
  map<string,map<string, string>> materias;
  std::mutex m;
};


#endif //INC_3TP_DB_H
