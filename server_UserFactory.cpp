#include "server_UserFactory.h"
#include "server_Admin.h"
#include "server_Alumno.h"
#include "server_Docente.h"
#include "server_MateriasDB.h"
#include <vector>
#include <string>
#include <stdexcept>
#define ALUMNO "alumno"
#define DOCENTE "docente"
#define ADMIN "admin"

User *UserFactory::createUser(vector<string> &params,
                              UsuariosDB &usersDB,
                              MateriasDB &materiasDB) const {
    User *ptr;
    string userType = params[0];

//    cout << "de materiasDB" << materiasDB.listAll() << endl;
    if (userType == ALUMNO){
        string id = params[1];
        ptr = new Alumno(ALUMNO, usersDB, materiasDB, id);
    } else if (userType == DOCENTE){
        string id = params[1];
        ptr = new Docente(DOCENTE, usersDB, materiasDB, id);
    } else if (userType == ADMIN){
        ptr = new Admin(ADMIN, usersDB, materiasDB);
    } else {
        throw std::invalid_argument(userType + " es un tipo de usuario "
                                                        "inválido.");
    }

    return ptr;
}
