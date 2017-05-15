#include "server_UserFactory.h"
#include "server_Admin.h"
#include "server_Alumno.h"
#include "server_Docente.h"
//#include <vector>
#include <string>
#include <stdexcept>
#include <deque>
#define ALUMNO "alumno"
#define DOCENTE "docente"
#define ADMIN "admin"

User *UserFactory::createUser(std::deque<string> &params, DB &database) const {
    User *ptr;
    string userType = params.front();
    params.pop_front();


//    TODO chequear si hay leaks cuando el usuario esta mal


    if (userType == ALUMNO){
        string id = params.front();;
        ptr = new Alumno(database, id);
    } else if (userType == DOCENTE){
        string id = params.front();
        ptr = new Docente(database, id);
    } else if (userType == ADMIN){
        ptr = new Admin(database);
    } else {
        throw std::invalid_argument(userType + " es un tipo de usuario "
                                                        "inválido.");
    }

    return ptr;
}
