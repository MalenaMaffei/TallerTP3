#include "server_StringFiller.h"
#include <vector>
#include <regex>
#include <map>
#include <string>

using std::vector;
using std::regex;
using std::string;
using std::map;

void StringFiller::splitStr(string str, vector<string> &params,
                            string delimiter){
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        if (token.size() > 0 && (token != " ")) {
            params.push_back(token);
        }
        str.erase(0, pos + delimiter.length());
    }
    if (str.size() > 0 && (str != " ")){
        params.push_back(str);
    }
}

string StringFiller::fillNameById(string format, map<string, string> &users) {
    string filled;
    std::istringstream iss(format);

    string line;
    while (getline(iss, line)){
//        regex rgx(".*#(\\w+).*");
//        string id = getMatch(rgx, line);
//        line = std::regex_replace(line, regex("#"+id),users[id]);
//                                  users[id]["nombre"]);
        line = fillLine(line, users, "#");
        line += "\n";
        filled += line;
    }
    return filled;
}

string StringFiller::getMatch(regex pattern, string str){
    std::smatch match;
    std::regex_search(str, match, pattern);
    string token = match[1];
    return token;
}

std::string StringFiller::fillLine(std::string format,
                                   std::map<std::string, std::string> info,
                                   string tokenId) {
    string line = format;
    regex rgx(".*"+tokenId+"(\\w+).*");
    std::smatch match;
    while (std::regex_search(line, match, rgx)) {
        string token = match[1];
        line=std::regex_replace(line,regex(tokenId+token), info[token]);
    }
    return line;
}

string StringFiller::fillAllMaterias(string format,
                                     map<string, map<string, string>> &materias)
{
    string all;

    for (const auto& kv : materias) {
        map<string, string> info = materias[kv.first];
        all += fillLine(format, info, "%");
    }
    return all;
}

string StringFiller::fillString(string format,
                    vector<map<string, string>> &materiasVector) {
    string alumno = "%idalumno #alumno%idalumno\n";

    string all;

    for (size_t j = 0; j < materiasVector.size(); ++j)  {
        string line = format;
        map<string, string> info = materiasVector[j];
        all += fillLine(format, info, "%");

        regex rgx(".*%(\\w+).*");
        std::smatch match;

        vector<string> alumnos;
        splitStr(materiasVector[j]["inscriptos"], alumnos, " ");
        for (size_t i = 0; i <alumnos.size(); ++i) {
            line = alumno;
            while (std::regex_search(line, match, rgx)) {
                string token = getMatch(rgx, line);
                line=std::regex_replace(line,regex("%"+token),
                                        alumnos[i]);
            }
            all += line;
        }
    }

//    all = fillNameById(all);
    return all;
}
