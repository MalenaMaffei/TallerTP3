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

User *UserFactory::createUser(vector<string> &params, UsuariosDB usersDB) const {
    User *ptr;
    string userType = params[0];


    if (userType == ALUMNO){
        string id = params[1];
        ptr = new Alumno(ALUMNO,usersDB,id);
    } else if (userType == DOCENTE){
        string id = params[1];
        ptr = new Docente(DOCENTE,usersDB,id);
    } else if (userType == ADMIN){
        ptr = new Admin(ADMIN,usersDB);
    } else {
        throw std::invalid_argument(userType + " es un tipo de usuario "
                                                        "inválido.");
    }

    return ptr;
}
