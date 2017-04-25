#ifndef INC_3TP_MATERIASDB_H
#define INC_3TP_MATERIASDB_H

#include <string>
#include <map>
#include "server_DB.h"
using std::map;
using std::string;

class MateriasDB : public DB {
public:
    MateriasDB(string filename);
    string listAll();
private:
    map<string,map<string, string>> materias;
    void fillMap(string line);
};


#endif //INC_3TP_MATERIASDB_H
