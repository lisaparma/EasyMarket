#include "admin.h"
#include "userPremium.h"
#include <QMessageBox>
#include <typeinfo>

admin::admin(QString u, QString p, QString n, QString c, QDate d, bool s, QString te, float b, int l): userPremium(u,p, n,c,d,s,te,b,l){}

void admin::deleteUser(listaAccount* lista ,const QString& usern) {
    QList<account*>::iterator it;
    bool trovato=false;
    for(it=lista->listona.begin(); it != lista->listona.end() && !trovato; it++) {
        if((*it)->getUsername() == usern) {
            trovato=true;
            lista->listona.erase(it);
        }
    }
}
void admin::upgradeAccount(listaAccount* lista, const QString& user) {
    QList<account*>::iterator it;
    bool trovato=false;
    for(it=lista->listona.begin(); it != lista->listona.end() && !trovato; it++) {
        if((*it)->getUsername() == user) {
            //Controllo se è userBase (anche se il pulsante sarà disattivato in caso contrario)
            if(typeid(**it)==typeid(userBase))
            {
               userBase* UB =dynamic_cast<userBase*>(*it);
               userPremium* UP = new userPremium(UB->getUsername(),
                                                 UB->getPassword(),
                                                 UB->getNome(),
                                                 UB->getCognome(),
                                                 UB->getData(),
                                                 UB->getSesso());
               lista->listona.erase(it);
               lista->listona.push_back(UP);
               QMessageBox q;
               q.setText("Upgrade eseguito con successo");
               q.exec();
               trovato=true;
            }
        }
    }
}
void admin::downgradeAccount(listaAccount* lista, const QString& user) {
    QList<account*>::iterator it;
    bool trovato=false;
    for(it=lista->listona.begin(); it != lista->listona.end() && !trovato; it++) {
        if((*it)->getUsername() == user) {
            //Controllo se è un userPremium (anche se il pulsante sarà già disattivato in caso contrario)
            if(typeid(**it)==typeid(userPremium))
            {
                userPremium* UP =dynamic_cast<userPremium*>(*it);
                userBase* UB = new userBase(UP->getUsername(),
                                               UP->getPassword(),
                                               UP->getNome(),
                                               UP->getCognome(),
                                               UP->getData(),
                                               UP->getSesso());
                lista->listona.erase(it);
                lista->listona.push_back(UB);
                QMessageBox q;
                q.setText("Downgrade eseguito con successo");
                q.exec();
                trovato=true;
            }
        }
    }
}

