#ifndef ADMIN_H
#define ADMIN_H

#include "listaaccount.h"
#include "userPremium.h"
#include <QString>


class admin: public userPremium
{
public:
    admin(QString, QString, QString, QString, QDate, bool, QString , float, int);

    void deleteUser(listaAccount*, const QString&);
    void upgradeAccount(listaAccount*, const QString&);
    void downgradeAccount(listaAccount*, const QString&);
};

#endif // ADMIN_H
