#include "server_DB.h"
#include "server_StringFiller.h"
#include <fstream>
#include <vector>
//#include <iostream>
//#include <regex>
//#include <sstream>
//#include <vector>
#include <map>
#include <string>
//#include "server_DBException.h"
//#include "server_User.h"
#define DELIMITER "\t"
using std::ifstream;
using std::vector;
using std::string;

DB::DB(string usuariosFile, string materiasFile) {
    fillUsuarios(usuariosFile);
    fillMaterias(materiasFile);
}

void DB::fillMaterias(string materiasFile) {
    StringFiller filler;
    string line;
    ifstream file;

    file.open(materiasFile);
    while (getline(file, line)){
        vector<string> words;
        filler.splitStr(line, words, DELIMITER);

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
    StringFiller filler;

    string line;
    ifstream file;
    file.open(usuariosFile);
    while (getline(file, line)){
        map<string ,string> info;
        vector<string> words;
        filler.splitStr(line, words, DELIMITER);
        string key = words[0] + words[1];
//        string info = words[2];
        info["inscripciones"] = "";
        info["nombre"] = words[2];
        users[key] = info;
    }
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
//    std::lock_guard<std::mutex> lock(m);
//    transaction.updateInscriptions(materias[transaction.getId()]);
    acceptTransaction(transaction);
}

void DB::processTransaction(Transaction &transaction, User &user) {
    validateTransaction(transaction);
//    std::lock_guard<std::mutex> lock(m);
//    transaction.updateInscriptions(materias[transaction.getId()]);
    acceptTransaction(transaction);
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

void DB::acceptTransaction(Transaction &transaction) {
    std::lock_guard<std::mutex> lock(m);
//
////    string alumnoId = transaction.getAlumnoId();
////    string inscripciones = users["alumno"+alumnoId]["inscripciones"];
////    string inscriptos = materias[transaction.getId()]["inscriptos"];
////    string vacantes = materias[transaction.getId()]["vacantes"];
////    string inscripciones = "";
    transaction.updateInscriptions(materias[transaction.getId()]);
//
////    users["alumno"+alumnoId]["inscripciones"] = inscripciones;
////    materias[transaction.getId()]["inscriptos"] = inscriptos;
////    materias[transaction.getId()]["vacantes"] = vacantes;
}

string DB::listarMateriasCabecera(string format, Admin &user) {
//    format = fillNameById(format);
    StringFiller filler;
    std::vector<map<string, string>> materiasVector;
    for (const auto& kv : materias) {
        materiasVector.push_back(materias[kv.first]);
    }
    string filled = filler.fillString(format, materiasVector);
    return filler.fillNameById(filled, users);
}

string DB::listarMateriasCabecera(string format, Alumno &user) {
    StringFiller filler;
    string all;
    string alumnoId = user.getId();
    for (const auto& kv : materias) {
        map<string, string> info = materias[kv.first];
//        if (info["inscriptos"].find(alumnoId) == string::npos){ continue; }
        if (alumnoAttendsMateria(kv.first, alumnoId)){
            all += filler.fillLine(format, info);
        }
    }
    all = filler.fillNameById(all, users);
    return all;
}

string DB::listarMateriasCabecera(string format, Docente &user) {
    StringFiller filler;
    std::vector<map<string, string>> materiasVector;
    for (const auto& kv : materias) {
        if (docenteTeachesMateria(kv.first, user.getId())){
            materiasVector.push_back(materias[kv.first]);
        }
    }

    string filled = filler.fillString(format, materiasVector);
    return filler.fillNameById(filled, users);
}

string DB::fillAllMaterias(string format){
    string all;
    StringFiller filler;
    for (const auto& kv : materias) {
        map<string, string> info = materias[kv.first];
        all += filler.fillLine(format, info);
    }
    all = filler.fillNameById(all, users);
    return all;
}

bool DB::docenteTeachesMateria(string materiaid, string iddocente) {
    return (iddocente == materias[materiaid]["iddocente"]);
}

bool DB::alumnoAttendsMateria(string materiaid, string alumnoId) {
    return (materias[materiaid]["inscriptos"].find(alumnoId) != string::npos);
//    return (idalumno == materias[materiaid]["inscriptos"]);
}
