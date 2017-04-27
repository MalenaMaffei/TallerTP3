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

 private:
  void fillMaterias(string materiasFile);
  void fillUsuarios(string line);
  std::map<string,string> users;
  map<string,map<string, string>> materias;
};


#endif //INC_3TP_DB_H
