#ifndef TP2_USER_H
#define TP2_USER_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class User {
public:
    User(const string &userType);

    void listarMaterias() const;

    virtual ~User();

    virtual void listarInscripciones() const;
//    TODO como hago con los que tienen parametro extra?
    virtual void inscribir(string codigo, string curso) const;
    virtual void desinscribir(string codigo, string curso) const;
    string print() const;

private:
    string userType;
};


#endif //TP2_USER_H


