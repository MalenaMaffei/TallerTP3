#include "server_UserFactory.h"
#include "server_Admin.h"
#include "server_Alumno.h"
#include "server_Docente.h"
#include <vector>
#include <string>
#define ALUMNO "alumno"
#define DOCENTE "docente"
#define ADMIN "admin"

User *UserFactory::createUser(vector<string> & params) const {
    User *ptr;
    string userType = params[0];

    if (userType == ALUMNO){
        ptr = new Alumno();
    } else if (userType == DOCENTE){
        ptr = new Docente();
    } else if (userType == ADMIN){
        ptr = new Admin();
    } else {
        cout << "tipo no bueno" << endl;
        return nullptr; }
//    TODO lanzar error aca si no era ninguno de esos

    return ptr;
}
