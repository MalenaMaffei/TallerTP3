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

User *UserFactory::createUser(vector<string> & params) const {
    User *ptr;
    string userType = params[0];
    string id = params[1];

    if (userType == ALUMNO){
        ptr = new Alumno(ALUMNO,id);
    } else if (userType == DOCENTE){
        ptr = new Docente(DOCENTE,id);
    } else if (userType == ADMIN){
        ptr = new Admin(ADMIN);
    } else {
        throw std::invalid_argument( userType + " es un tipo de usuario "
                                                        "inválido." );
    }

    return ptr;
}
