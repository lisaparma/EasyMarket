#include "userPremium.h"
#include <time.h>

userPremium::userPremium(QString u, QString p, QString n, QString c, QDate d, bool s, QString te, float cr, int pu):
    userBase(u,p,n,c,d,s),
    tessera(te),
    credito(cr),
    punti(pu)
{
    if(te=="0") {
        int r=(rand()%10000)+10100000;
        tessera=QString::number(r);
    }
}

// Metodi get
QString userPremium::getTessera() const {return tessera;}
float userPremium::getCredito() const {return credito;}
int userPremium::getPunti() const {return punti;}

// Metodi set
void userPremium::setCredito(float x) {
    credito=x;
}

void userPremium::setPunti(int x) {
    punti=x;
}

float userPremium::soldiSpesa() const {
    float soldi=0;
    QList<articolo>::const_iterator i;
    for(i=spesa.begin(); i!=spesa.end(); ++i) {
        soldi += (i->prod->prezzoScontato()*(i->getQuantita()));
    }
    return soldi;
}

int userPremium::puntiBonusSpesa() const {
    int punti=0;
    QList<articolo>::const_iterator i;
    for(i=spesa.begin(); i!=spesa.end(); ++i) {
        punti += (i->prod->getBonus()*(i->getQuantita()));
    }
    return punti;
}
