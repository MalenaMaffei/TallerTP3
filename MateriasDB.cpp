#include "MateriasDB.h"
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
    info["iddocente"] = words[3];
    info["vacantes"] = words[4];
    materias[key] = info;
}

MateriasDB::MateriasDB(string filename) : DB(filename, std::__cxx11::string()) {
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
            string line = format;
//            all =all + kv.first + " has value ";
            map<string, string> info = materias[kv.first];
            std::regex rgx(".*\\$(\\w+).*");
            std::smatch match;
            while (std::regex_search(line, match, rgx)) {
                std::smatch match;
                std::regex_search(line, match, rgx);
                string token = match[1];

                line = std::regex_replace(line, regex("\\$"+token), info[token]);
            }
            all += line;
        }
    std::cout << all << std::endl;
        return all;
}
