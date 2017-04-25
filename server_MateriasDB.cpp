#include "server_MateriasDB.h"
#include <fstream>
#include <vector>
#include <iostream>
using std::ifstream;
using std::vector;

void MateriasDB::fillMap(string line) {
    vector<string> words;
    splitStr(line, words);

    string key = words[0] + words[1];
    map<string ,string> info;
    info["descripcion"] = words[2];
    info["id-docente"] = words[3];
    info["vacantes"] = words[4];
    materias[key] = info;
}

MateriasDB::MateriasDB(string filename) : DB(filename) {
    string line;
    ifstream file;
    file.open(filename);
    while (getline(file, line)){
        fillMap(line);
    }
}
string MateriasDB::listAll() {
    return "sin implementar";
}
