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
        info["inscriptos"] = "";
        materias[key] = info;
    }
}

void DB::fillUsuarios(string usuariosFile){
    string line;
    ifstream file;
    file.open(usuariosFile);
    while (getline(file, line)){
        map<string ,string> info;
        vector<string> words;
        splitStr(line, words);
        string key = words[0] + words[1];
//        string info = words[2];
        info["inscripciones"] = "";
        info["nombre"] = words[2];
        users[key] = info;
    }
}

bool DB::userExists(string userType, string id) const {
    return users.find(userType+id) != users.end();
}

bool DB::materiaExists(string materia) const {
    for (const auto& kv : materias) {
        if(kv.first.find(materia) != string::npos){
            return true;
        }
    }
    return false;
}

bool DB::cursoExists(string materia, string curso) const{
    return materias.find(materia+"-"+curso) != materias.end();
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
        line = std::regex_replace(line, std::regex("#"+id),
                                  users[id]["nombre"]);
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
    return all;
}

bool DB::vacantesExist(string materia, string curso) {
    return stoi(materias[materia+"-"+curso]["vacantes"]) > 0;
}


bool DB::newInscription(string materia, string curso, string alumnoId) {
    string materiaId = materia+"-"+curso;
    string inscripciones = users["alumno"+alumnoId]["inscripciones"];
    if (inscripciones.find(materia) != string::npos){ return false; }
    materias[materiaId]["inscriptos"] += " "+alumnoId;
    users["alumno"+alumnoId]["inscripciones"] += " "+materiaId;
    string vacantes = materias[materiaId]["vacantes"];
    int new_vacantes = stoi(vacantes) - 1;
    materias[materiaId]["vacantes"] = std::to_string(new_vacantes);
    return true;
}

bool DB::docenteTeachesMateria(string materia, string curso,string docenteId) {
    return docenteId == materias[materia+"-"+curso]["iddocente"];
}

