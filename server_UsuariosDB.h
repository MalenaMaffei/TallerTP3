#ifndef INC_3TP_USUARIOSDB_H
#define INC_3TP_USUARIOSDB_H

#include <string>
#include <map>
#include "server_DB.h"
using std::map;
using std::string;

class UsuariosDB : public DB {
public:
    UsuariosDB(string filename);
    bool userExists(string userType, string id) const;
    void fillMap(string line);

protected:

private:
    std::map<string,string> users;
//  std::map<string,map<string, string>> users;


};


#endif //INC_3TP_USUARIOSDB_H
