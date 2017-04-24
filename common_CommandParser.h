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
    void parseCommand(string recv_command, vector<string> &commands) const;
    string delimitCommands(vector<string> arguments) const;
};



#endif //TP2_COMMANDPARSER_H
