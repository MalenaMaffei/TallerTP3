#include "server_DB.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <sstream>
#include <map>
#include <string>
#include "server_DBException.h"
#include "server_User.h"
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

            line=std::regex_replace(line,std::regex("\\$"+token), info[token]);
        }
        all += line;
    }
    return all;
}

bool keyExists(map<string,map<string, string>> & mapa, string key) {
    return mapa.find(key) != mapa.end();
}

void DB::validateUser(string userType, string id) {
    if (!keyExists(users, userType+id)){
        throw DBException("El"+userType+" "+id+" es inválido.\n");
    }
}

void DB::validateTransaction(Transaction transaction){
    validateMateria(transaction.getMateria(), transaction.getCurso());
    validateUser("alumno", transaction.getAlumnoId());
}

void DB::validateDocente(Transaction &transaction, string docenteId) {
    if (! (docenteId == materias[transaction.getId()]["iddocente"])) {
        throw DBPermissionException("No tiene permisos para operar sobre "
                                        ""+transaction.getMateria()+", curso "
            ""+transaction.getCurso()+".\n");
    }
}

void DB::processTransaction(Transaction &transaction, Docente &docente) {
    validateTransaction(transaction);
    validateDocente(transaction, docente.getId());
    string alumnoId = transaction.getAlumnoId();
    string inscripciones = users["alumno"+alumnoId]["inscripciones"];
    string inscriptos = materias[transaction.getId()]["inscriptos"];
    string vacantes = materias[transaction.getId()]["vacantes"];

    transaction.updateInscriptions(inscriptos,inscripciones,  vacantes);

    users["alumno"+alumnoId]["inscripciones"] = inscripciones;
    materias[transaction.getId()]["inscriptos"] = inscriptos;
    materias[transaction.getId()]["vacantes"] = vacantes;
}

void DB::processTransaction(Transaction &transaction, User &user) {
    validateTransaction(transaction);
    string alumnoId = transaction.getAlumnoId();
    string inscripciones = users["alumno"+alumnoId]["inscripciones"];
    string inscriptos = materias[transaction.getId()]["inscriptos"];
    string vacantes = materias[transaction.getId()]["vacantes"];

    transaction.updateInscriptions(inscriptos,inscripciones,  vacantes);

    users["alumno"+alumnoId]["inscripciones"] = inscripciones;
    materias[transaction.getId()]["inscriptos"] = inscriptos;
    materias[transaction.getId()]["vacantes"] = vacantes;
}

bool DB::materiaExists(string materia) const {
    for (const auto& kv : materias) {
        if (kv.first.find(materia) != string::npos){
            return true;
        }
    }
    return false;
}

void DB::validateMateria(string materia, string curso) {
    if (!materiaExists(materia)){
        throw DBException("La materia "+materia+" no es válida.\n");
    }
    string materiaId = materia+"-"+curso;
    if (! keyExists(materias, materiaId)){
        throw DBException("El curso "+curso+" en la materia "+materia+ " no es "
            "válido.\n");
    }
}





