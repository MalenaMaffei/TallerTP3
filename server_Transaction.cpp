#include "server_Transaction.h"
Transaction::Transaction(const string &materia,const string &curso,
                         const string &alumnoId)
    : materia(materia), curso(curso), alumnoId(alumnoId) {
    id = materia+"-"+curso;
}
const string &Transaction::getMateria() const {
    return materia;
}
const string &Transaction::getCurso() const {
    return curso;
}
const string &Transaction::getId() const {
    return id;
}
const string &Transaction::getAlumnoId() const {
    return alumnoId;
}
