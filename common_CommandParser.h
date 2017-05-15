#ifndef TP2_COMMANDPARSER_H
#define TP2_COMMANDPARSER_H

#include <string>
#include <vector>
#include <deque>


class CommandParser {
public:
    std::string buildCommand(std::string userInput) const;
    void parseUserInfo(std::string userInfo, std::deque<std::string> &params)
        const;
    void parseCommand(std::string recv_command,
                      std::deque<std::string> &commands) const;
    std::string delimitCommands(std::deque<std::string> arguments) const;
};



#endif //TP2_COMMANDPARSER_H
