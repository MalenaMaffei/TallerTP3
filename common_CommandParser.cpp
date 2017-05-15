#include "common_CommandParser.h"
#include <algorithm>
//#include <vector>
#include <string>
#include <deque>
#include <stdexcept>
#define LISTARMATERIAS "listarMaterias"
#define LM_CODE "lm"

#define LISTARINSCRIPCIONES "listarInscripciones"
#define LI_CODE "li"

#define INSCRIBIR "inscribir"
#define IN_CODE "in"

#define DESINSCRIBIR "desinscribir"
#define DES_CODE "de"

#define COMM_DELIMITER "-"
#define STR_DELIMITER " "

using std::deque;
using std::string;

string CommandParser::delimitCommands(deque<string> arguments) const{
    string message;
    std::for_each(arguments.begin(), arguments.end(), [&](string a){
        message = message + a + "-";
    });
    message.pop_back();
    return message;
}

void splitString(string str, deque<string> &params, string delimiter){
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        params.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    params.push_back(str);
}

string CommandParser::buildCommand(string str) const {
    deque<string> userInput;
    splitString(str, userInput, STR_DELIMITER);
    string & command_code = userInput.front();
    if (command_code == LISTARMATERIAS){
        command_code = LM_CODE;
    } else if (command_code == LISTARINSCRIPCIONES){
        command_code = LI_CODE;
    } else if (command_code == INSCRIBIR){
        command_code = IN_CODE;
    } else if (command_code == DESINSCRIBIR){
        command_code = DES_CODE;
    } else {
        throw std::invalid_argument(command_code + " es un codigo invalido");
    }

    return delimitCommands(userInput);
}

void CommandParser::parseUserInfo(string userInfo, deque<string> &params)
const {
    splitString(userInfo,params, COMM_DELIMITER);
}

void CommandParser::parseCommand(string recv_command,
                                 deque<string> &commands) const {
    splitString(recv_command, commands, COMM_DELIMITER);
}
