#include "account.h"

// Costruttore a due argomenti
account::account(QString u, QString p):
    username(u),
    password(p)
{}

//Metodi get
QString account::getUsername() const {return username;}
QString account::getPassword() const {return password;}

