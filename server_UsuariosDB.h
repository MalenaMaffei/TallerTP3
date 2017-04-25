//
// Created by Male on 4/24/17.
//

#ifndef INC_3TP_USUARIOSDB_H
#define INC_3TP_USUARIOSDB_H

#include <string>
#include <map>

using std::map;
using std::string;

class UsuariosDB {
public:
    UsuariosDB(string filename);
    bool userExists(string userType, string id) const;

private:
    std::map<string,string> users;
    void fillMap(string line);
};


#endif //INC_3TP_USUARIOSDB_H
