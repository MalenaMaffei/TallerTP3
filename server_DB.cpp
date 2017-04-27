#include "server_DB.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#define DELIMITER "\t"
using std::ifstream;
using std::vector;
using std::string;


void splitStr(string str, vector<string> &params){
    size_t pos = 0;
    string token;
    string delimiter = DELIMITER;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        params.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    params.push_back(str);
}

DB::DB(string usuariosFile, string materiasFile) {

    fillUsuarios(usuariosFile);
    fillMaterias(materiasFile);
//    string line;
//    ifstream file;
//
//    file.open(usuariosFile);
//    while (getline(file, line)){
//        fillUsuarios(line);
//    }
}

void DB::fillMaterias(string materiasFile) {
    string line;
    ifstream file;

    file.open(materiasFile);
    while (getline(file, line)){
        vector<string> words;
        splitStr(line, words);

        string key = words[0] +"-" +words[1];
        map<string ,string> info;
        info["codigo"] = words[0];
        info["curso"] = words[1];
        info["descripcion"] = words[2];
        info["iddocente"] = words[3];
        info["vacantes"] = words[4];
        materias[key] = info;
    }
}

void DB::fillUsuarios(string usuariosFile){
    string line;
    ifstream file;
    file.open(usuariosFile);
    while (getline(file, line)){
        vector<string> words;
        splitStr(line, words);
        string key = words[0] + words[1];
        string info = words[2];
        users[key] = info;
    }
}

bool DB::userExists(string userType, string id) const {
    return users.find(userType+id) != users.end();
}

string DB::fillNameById(string format) {
    string filled;
    std::istringstream iss(format);

    string line;
    while (getline(iss, line)){
        std::regex rgx(".*#(\\w+).*");
        std::smatch match;
        std::regex_search(line, match, rgx);
        string id = match[1];
        line = std::regex_replace(line, std::regex("#"+id), users[id]);
        line += "\n";
        filled += line;
    }
    return filled;
}

string DB::fillAllMaterias(string format){
    string all;

    for (const auto& kv : materias) {
        string line = format;
        map<string, string> info = materias[kv.first];
        std::regex rgx(".*\\$(\\w+).*");
        std::smatch match;
        while (std::regex_search(line, match, rgx)) {
            std::smatch match;
            std::regex_search(line, match, rgx);
            string token = match[1];

            line = std::regex_replace(line,std::regex("\\$"+token), info[token]);
        }
        all += line;
    }
    std::cout << all << std::endl;
    return all;
}

