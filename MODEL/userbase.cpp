#include "userBase.h"

// Costruttore 4 argomenti: username, password. nome e cognome
userBase::userBase(QString u, QString p, QString nom, QString cog, QDate d, bool s):
    account(u,p),
    Nome(nom),
    Cognome(cog),
    nascita(d),
    sesso(s)
{}

// Metodi get
QString userBase::getNome() const {return Nome;}
QString userBase::getCognome() const {return Cognome;}
QDate userBase::getData() const {return nascita;}
bool userBase::getSesso() const {return sesso;}

float userBase::soldiSpesa() const {
    float soldi=0;
    QList<articolo>::const_iterator i;
    for(i=spesa.begin(); i!=spesa.end(); ++i) {
        soldi += (i->prod->getPrezzo()*(i->getQuantita()));
    }
    return soldi;
}
