#ifndef INC_3TP_MATERIASDB_H
#define INC_3TP_MATERIASDB_H

#include <string>
#include <map>

using std::map;
using std::string;

class MateriasDB {
public:
    MateriasDB(string filename);

private:
    map<string,map<string, string>> classes;
};


#endif //INC_3TP_MATERIASDB_H
