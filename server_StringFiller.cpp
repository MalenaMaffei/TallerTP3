#include "server_StringFiller.h"
#include <vector>
//#include <sstream>
#include <regex>
#include <map>
#include <string>
//#include <iostream>
//using std::ifstream;
using std::vector;

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

string StringFiller::fillNameById(string format,
                                  map<string, map<string,string>> & users) {
    string filled;
    std::istringstream iss(format);

    string line;
    while (getline(iss, line)){
        std::regex rgx(".*#(\\w+).*");
        std::smatch match;
        std::regex_search(line, match, rgx);
        string id = match[1];
        line = std::regex_replace(line, std::regex("#"+id),
                                  users[id]["nombre"]);
        line += "\n";
        filled += line;
    }
    return filled;
}


string StringFiller::fillLine(string format, map<string, string> info){
    string line = format;
    std::regex rgx(".*\\$(\\w+).*");
    std::smatch match;
    while (std::regex_search(line, match, rgx)) {
        std::smatch match;
        std::regex_search(line, match, rgx);
        string token = match[1];

        line=std::regex_replace(line,std::regex("\\$"+token), info[token]);
    }
    return line;
}


string StringFiller::fillAllMaterias(string format,
                                     map<string, map<string, string>> &materias)
{
    string all;

    for (const auto& kv : materias) {
        map<string, string> info = materias[kv.first];
        all += fillLine(format, info);
    }
    return all;
}

string StringFiller::fillString(string format,
                    vector<map<string, string>> &materiasVector) {
    string alumno = "$idalumno #alumno$idalumno\n";

    string all;

    for (size_t j = 0; j < materiasVector.size(); ++j)  {
        string line = format;
        map<string, string> info = materiasVector[j];
        all += fillLine(format, info);

        std::regex rgx(".*\\$(\\w+).*");
        std::smatch match;

        vector<string> alumnos;
        splitStr(materiasVector[j]["inscriptos"], alumnos, " ");
        for (size_t i = 0; i <alumnos.size(); ++i) {
            line = alumno;
            while (std::regex_search(line, match, rgx)) {
                std::smatch match;
                std::regex_search(line, match, rgx);
                string token = match[1];

                line=std::regex_replace(line,std::regex("\\$"+token),
                                        alumnos[i]);
            }
            all += line;
        }
    }

//    all = fillNameById(all);
    return all;
}
