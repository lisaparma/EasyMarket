#ifndef LISTAACCOUNT_H
#define LISTAACCOUNT_H

#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "account.h"

class listaAccount
{
private:
    QXmlStreamWriter* xmlUserWriter;
    QXmlStreamReader* xmlUserReader;
public:
    QList<account*> listona;

    listaAccount();

    void cleanfile();
    void saveAccount();
    void loadAccount();


};


#endif // LISTAACCOUNT_H
