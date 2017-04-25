#include <fstream>
#include "server_UsuariosDB.h"
#include <vector>
#include <iostream>
#define DELIMITER "\t"
using std::ifstream;
using std::vector;


void UsuariosDB::fillMap(string line){
    vector<string> words;
    splitStr(line, words);
    string key = words[0] + words[1];
    string value = words[2];
    users[key] = value;
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
