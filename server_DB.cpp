#include "server_DB.h"
#include <fstream>
#include <vector>
#include <iostream>
#define DELIMITER "\t"
using std::ifstream;
using std::vector;
using std::string;


void DB::splitStr(string str, vector<string> &params){
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

DB::DB(string filename) {
//    string line;
//    ifstream file;
//
//    file.open(filename);
//    while (getline(file, line)){
//        fillMap(line);
//    }
}
void DB::fillMap(string line) {
    std::cout << "hola de fillmap de base" << std::endl;
}
