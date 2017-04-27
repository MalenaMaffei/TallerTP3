#include "server_UserFactory.h"
#include "server_Admin.h"
#include "server_Alumno.h"
#include "server_Docente.h"
#include "MateriasDB.h"
#include <vector>
#include <string>
#include <stdexcept>
#define ALUMNO "alumno"
#define DOCENTE "docente"
#define ADMIN "admin"

User *UserFactory::createUser(vector<string> &params, DB &database) const {
    User *ptr;
    string userType = params[0];

//    cout << "de materiasDB" << materiasDB.listAll() << endl;
    if (userType == ALUMNO){
        string id = params[1];
        ptr = new Alumno(ALUMNO, database, id);
    } else if (userType == DOCENTE){
        string id = params[1];
        ptr = new Docente(DOCENTE, database, id);
    } else if (userType == ADMIN){
        ptr = new Admin(ADMIN, database);
    } else {
        throw std::invalid_argument(userType + " es un tipo de usuario "
                                                        "inválido.");
    }

    return ptr;
}
