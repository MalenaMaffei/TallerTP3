#include <fstream>
#include "server_UsuariosDB.h"
#include <vector>
#define DELIMITER "\t"
using std::ifstream;
using std::vector;

void splitStr(string str, vector<string> &params, string delimiter){
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        params.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    params.push_back(str);
}

void UsuariosDB::fillMap(string line){
    vector<string> words;
    splitStr(line, words, DELIMITER);
    string key = words[0] + words[1];
    string value = words[2];
    users[key] = value;
}

UsuariosDB::UsuariosDB(string filename) {
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
