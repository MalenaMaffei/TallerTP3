#include "server_UserFactory.h"
#include "server_Admin.h"
#include "server_Alumno.h"
#include "server_Docente.h"

//#define ALUMNO "alumno"

User *UserFactory::createUser(vector<string> & params) const {
    User *ptr;
    string userType = params[0];

    if (userType == "alumno"){
        ptr = new Alumno();
    } else if (userType == "docente"){
        ptr = new Docente();
    } else if (userType == "admin"){
        ptr = new Admin();
    } else {
        cout << "tipo no byeno" << endl;
        return nullptr; }
//    TODO lanzar error aca si no era ninguno de esos

    return ptr;
}
