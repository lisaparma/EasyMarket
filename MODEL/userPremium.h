#ifndef USERPREMIUM_H
#define USERPREMIUM_H
#include "userBase.h"

class userPremium: public userBase
{
private:
    QString tessera;
    float credito;
    int punti;
public:
    userPremium(QString, QString, QString, QString, QDate, bool, QString te="0", float cr=0, int pu=0);

    QString getTessera() const;
    float getCredito() const;
    int getPunti() const;

    void setCredito(float);
    void setPunti(int);

    virtual float soldiSpesa() const;
    int puntiBonusSpesa() const;
};

#endif // USERPREMIUM_H
