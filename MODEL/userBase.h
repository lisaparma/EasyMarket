#ifndef USERBASE_H
#define USERBASE_H

#include "articolo.h"
#include <QtCore>
#include "account.h"

class userBase: public account
{
private:
    QString Nome;
    QString Cognome;
    QDate nascita;
    bool sesso;
public:
    QList<articolo> spesa;
    userBase(QString, QString, QString, QString, QDate, bool);

    QString getNome() const;
    QString getCognome() const;
    QDate getData() const;
    bool getSesso() const;

    virtual float soldiSpesa() const;



};

#endif // USERBASE_H
