#include "common_CommandParser.h"
#include <algorithm>
#include <vector>
#include <string>
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

string CommandParser::delimitCommands(vector<string> arguments) const{
    string message;
    std::for_each(arguments.begin(), arguments.end(), [&](string a){
        message = message + a + "-";
    });
    message.pop_back();
    return message;
}

void splitString(string str, vector<string> &params, string delimiter){
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        params.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    params.push_back(str);
}

string CommandParser::buildCommand(string str) const {
    vector<string> userInput;
    splitString(str, userInput, STR_DELIMITER);
    string command_code = userInput[0];
    if (command_code == LISTARMATERIAS){
//      TODO  chequear argumentos correctos
        userInput[0] = LM_CODE;
    } else if (command_code == LISTARINSCRIPCIONES){
        userInput[0] = LI_CODE;
    } else if (command_code == INSCRIBIR){
        userInput[0] = IN_CODE;
    } else if (command_code == DESINSCRIBIR){
        userInput[0] = DES_CODE;
    } else {
//        TODO LANZAR ERROR ACA
    }

    return delimitCommands(userInput);
}

void CommandParser::parseUserInfo(string userInfo, vector<string> &params)
const {
    splitString(userInfo,params, COMM_DELIMITER);
}
void CommandParser::parseCommand(string recv_command,
                                 vector<string> &commands) const {
    splitString(recv_command, commands, COMM_DELIMITER);
}
