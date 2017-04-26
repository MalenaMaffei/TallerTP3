#include <fstream>
#include "server_UsuariosDB.h"
#include <vector>
#include <regex>
#include <iostream>
#include <sstream>
#define DELIMITER "\t"
using std::ifstream;
using std::vector;
using std::regex;

void UsuariosDB::fillMap(string line){
    vector<string> words;
    splitStr(line, words);
    string key = words[0] + words[1];
    string info = words[2];
//    map <string, string> info;
//    info["nombre"] = words[2];
    users[key] = info;
}

UsuariosDB::UsuariosDB(string filename) : DB(filename){
    string line;
    ifstream file;
    file.open(filename);
    while (getline(file, line)){
        fillMap(line);
    }
}

bool UsuariosDB::userExists(string userType, string id) const {
    return users.find(userType+id) != users.end();
}
string UsuariosDB::fillNameById(string format) {
    string filled;
    std::istringstream iss(format);

    string line;
    while (getline(iss, line)){
        std::regex rgx(".*#(\\w+).*");
        std::smatch match;
        std::regex_search(line, match, rgx);
        string id = match[1];
        line = std::regex_replace(line, regex("#"+id), users[id]);
        line += "\n";
        filled += line;
    }
    return filled;
}
