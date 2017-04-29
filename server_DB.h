#ifndef INC_3TP_DB_H
#define INC_3TP_DB_H
#include <string>
#include <map>
#include <vector>
#include "server_User.h"
#include "server_Docente.h"
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
  void newInscription(string materia, string curso, string alumnoId, Docente &user);
  void newInscription(string materia, string curso, string alumnoId, User &user);
  bool removeInscription(string materia, string curso, string alumnoId);
  void validateDocente(string materia, string curso, string docenteId);

 private:
  void fillMaterias(string materiasFile);
  void fillUsuarios(string line);
  void validateMateria(string materia, string curso);
  void modifyVacante(string materia, string curso, int cantidad);
  void validateInscription(string materia, string alumnoId);
  void addMateria(string materia, string curso, string alumnoId);

  std::map<string,map<string, string>> users;
  map<string,map<string, string>> materias;
};


#endif //INC_3TP_DB_H
