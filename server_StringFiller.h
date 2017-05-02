#ifndef TP2_STRINGFILLER_H
#define TP2_STRINGFILLER_H
#include <string>
#include <map>
#include <vector>
using std::string;
using std::map;
using std::vector;

class StringFiller {
 public:
  string fillNameById(string format, map<string, map<string,
                                                                   string>> &
  users);
  void splitStr(string str, vector<string> &params, string
  delimiter);
  string fillLine(string format, map<string, string> info);
  string fillAllMaterias(string format,
                           map<string, map<string, string>> &materias);
  string fillString(string format,
                                  vector<map<string, string>> &materiasVector);
};

#endif //TP2_STRINGFILLER_H
