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
  DB(string filename);
  virtual void fillMap(string line);

 protected:

  void splitStr(string str, vector<string> &params);

};


#endif //INC_3TP_DB_H
