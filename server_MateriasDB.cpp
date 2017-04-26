#include "server_MateriasDB.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>

using std::ifstream;
using std::vector;
using std::regex;
using std::regex_replace;

void MateriasDB::fillMap(string line) {
    vector<string> words;
    splitStr(line, words);

    string key = words[0] + words[1];
    map<string ,string> info;
    info["codigo"] = words[0];
    info["curso"] = words[1];
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
string MateriasDB::listAll(string format) {
        string all;
        for (const auto& kv : materias) {
//            all =all + kv.first + " has value ";
            map<string, string> info = materias[kv.first];
            string tmp;
            tmp = regex_replace(format, regex("\\<cod>"), info["codigo"]);
            tmp = regex_replace(tmp, regex("\\<desc>"), info["descripcion"]);
            tmp = regex_replace(tmp, regex("\\<id>"), info["curso"]);
            tmp = regex_replace(tmp, regex("\\<vac>"), info["vacantes"]);
            all += tmp;
//            for (const auto& kv : info) {

//                all += kv.second;
//            }
        }
        return all;
}
