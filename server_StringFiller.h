#ifndef TP2_STRINGFILLER_H
#define TP2_STRINGFILLER_H
#include <string>
#include <map>
#include <vector>
#include <regex>

class StringFiller {
 public:
  std::string fillNameById(std::string format,
                           std::map<std::string,std::string> &users);
  void splitStr(std::string str, std::vector<std::string> &params, std::string
  delimiter);
  std::string fillLine(std::string format,
                       std::map<std::string, std::string> info,
                       std::string tokenId);
//  std::string fillAllMaterias(std::string format,
//    std::map<std::string, std::map<std::string, std::string>> &materias);

 private:
  std::string getMatch(std::regex pattern, std::string str);
};

#endif //TP2_STRINGFILLER_H
