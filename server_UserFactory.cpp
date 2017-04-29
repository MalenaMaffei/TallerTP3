#include "server_UserFactory.h"
#include "server_Admin.h"
#include "server_Alumno.h"
#include "server_Docente.h"
#include <vector>
#include <string>
#include <stdexcept>
#define ALUMNO "alumno"
#define DOCENTE "docente"
#define ADMIN "admin"

User *UserFactory::createUser(vector<string> &params, DB &database) const {
    User *ptr;
    string userType = params[0];

//    TODO chequear si hay leaks cuando el usuario esta mal
//    cout << "de materiasDB" << materiasDB.listAll() << endl;
    if (userType == ALUMNO){
        string id = params[1];
        ptr = new Alumno(database, id);
    } else if (userType == DOCENTE){
        string id = params[1];
        ptr = new Docente(database, id);
    } else if (userType == ADMIN){
        ptr = new Admin(database);
    } else {
        throw std::invalid_argument(userType + " es un tipo de usuario "
                                                        "inválido.");
    }

    return ptr;
}
