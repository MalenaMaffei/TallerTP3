#include "server_DB.h"
#include "server_StringFiller.h"
#include <fstream>
#include <vector>
#include <map>
#include <string>
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
        vector<string> words;
        filler.splitStr(line, words, DELIMITER);
        string key = words[0] + words[1];
        users[key] = words[2];
    }
}

bool keyExists(map<string,map<string, string>> & mapa, string key) {
    return mapa.find(key) != mapa.end();
}

void DB::validateUser(string userType, string id) {
    if (!users.count(userType+id)){
        throw DBException("El"+userType+" "+id+" es inválido.\n");
    }
}

void DB::validateTransaction(Transaction transaction){
    validateMateria(transaction.getMateria(), transaction.getCurso());
    validateUser("alumno", transaction.getAlumnoId());
}

void DB::validateDocente(Transaction &transaction, string docenteId) {
    if (! docenteTeachesMateria(transaction.getId(), docenteId)) {
        throw DBPermissionException("No tiene permisos para operar sobre "
                                        ""+transaction.getMateria()+", curso "
            ""+transaction.getCurso()+".\n");
    }
}

void DB::processTransaction(Transaction &transaction, Docente &docente) {
    validateTransaction(transaction);
    validateDocente(transaction, docente.getId());
    acceptTransaction(transaction);
}

void DB::processTransaction(Transaction &transaction, User &user) {
    validateTransaction(transaction);
    acceptTransaction(transaction);
}

void DB::validateMateria(string materia, string curso) {
    bool found = false;
    for (const auto& kv : materias) {
        if (kv.first.find(materia) != string::npos){
            found = true;
        }
    }
    if (!found){
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
    transaction.updateInscriptions(materias[transaction.getId()]);
}

string DB::listarMateriasCabecera(string format, Admin &user) {
    string alumnoFormat = "%idalumno #alumno%idalumno\n";
    StringFiller filler;
    string filled;
    for (const auto& kv : materias) {
        filled += filler.fillLine(format, materias[kv.first], "%");
        vector<string> alumnos;
        filler.splitStr(materias[kv.first]["inscriptos"], alumnos, " ");
        for (size_t i = 0; i <alumnos.size(); ++i) {
            map<string, string> ids;
            ids["idalumno"] = alumnos[i];
            filled += filler.fillLine(alumnoFormat, ids, "%");
        }
    }
    return filler.fillNameById(filled, users);
}

string DB::listarMateriasCabecera(string format, Docente &user) {
    StringFiller filler;
    string alumnoFormat = "%idalumno #alumno%idalumno\n";
    string filled;
    for (const auto& kv : materias) {
        if (docenteTeachesMateria(kv.first, user.getId())){
            filled += filler.fillLine(format, materias[kv.first], "%");
            vector<string> alumnos;
            filler.splitStr(materias[kv.first]["inscriptos"], alumnos, " ");
            for (size_t i = 0; i <alumnos.size(); ++i) {
                map<string, string> ids;
                ids["idalumno"] = alumnos[i];
                filled += filler.fillLine(alumnoFormat, ids, "%");
            }
        }
    }
    return filler.fillNameById(filled, users);
}

string DB::listarMateriasCabecera(string format, Alumno &user) {
    StringFiller filler;
    string all;
    string alumnoId = user.getId();
    for (const auto& kv : materias) {
        map<string, string> info = materias[kv.first];
        if (alumnoAttendsMateria(kv.first, alumnoId)){
            all += filler.fillLine(format, info, "%");
        }
    }
    all = filler.fillNameById(all, users);
    return all;
}

string DB::fillAllMaterias(string format){
    string all;
    StringFiller filler;
    for (const auto& kv : materias) {
        map<string, string> info = materias[kv.first];
        all += filler.fillLine(format, info,"%");
    }
    all = filler.fillNameById(all, users);
    return all;
}

bool DB::docenteTeachesMateria(string materiaid, string iddocente) {
    return (iddocente == materias[materiaid]["iddocente"]);
}

bool DB::alumnoAttendsMateria(string materiaid, string alumnoId) {
    return (materias[materiaid]["inscriptos"].find(alumnoId) != string::npos);
}
