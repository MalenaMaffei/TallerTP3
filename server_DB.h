#ifndef INC_3TP_DB_H
#define INC_3TP_DB_H
#include <string>
#include <map>
#include <vector>
using std::map;
using std::string;
using std::vector;

class DB {
 public:
  DB(string usuariosFile, string materiasFile);
  string fillAllMaterias(string format);
  string fillNameById(string format);
  bool userExists(string userType, string id) const;
  bool materiaExists(string materia) const;
  bool cursoExists(string materiaId) const;
//  bool vacantesExist(string materia, string curso);
  bool newInscription(string materia, string curso, string alumnoId);
  bool removeInscription(string materia, string curso, string alumnoId);
  bool docenteTeachesMateria(string materia, string curso, string docenteId);

 private:
  void fillMaterias(string materiasFile);
  void fillUsuarios(string line);
  void validateMateria(string materia, string curso);
  void modifyVacante(string materia, string curso, int cantidad);
  std::map<string,map<string, string>> users;
  map<string,map<string, string>> materias;
};


#endif //INC_3TP_DB_H
