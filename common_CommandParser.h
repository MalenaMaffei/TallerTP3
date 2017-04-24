#ifndef TP2_COMMANDPARSER_H
#define TP2_COMMANDPARSER_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class CommandParser {
public:
    string buildCommand(string userInput) const;
    void parseUserInfo(string userInfo, vector<string> &params) const;
};



#endif //TP2_COMMANDPARSER_H
