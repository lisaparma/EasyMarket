#include "listaaccount.h"
#include "userPremium.h"
#include "admin.h"
#include <QMessageBox>

listaAccount::listaAccount(){}

void listaAccount::cleanfile() {
    QString userFilePath = ("../ProgettissimoP2/savedData/utenti.xml");
    QFile *userFile = new QFile(userFilePath);
    userFile->remove();
}

void listaAccount::saveAccount() {
    xmlUserWriter = new QXmlStreamWriter();
    QString userFilePath = ("../ProgettissimoP2/savedData/utenti.xml");
    QFile *userFile = new QFile(userFilePath);
    if (!userFile->open(QIODevice::ReadWrite)) {
        QMessageBox::warning(0, "Error!", "Error saving file");
    }
    else {
        xmlUserWriter->setDevice(userFile);
        xmlUserWriter->setAutoFormatting(true);
        xmlUserWriter->writeStartDocument();

        xmlUserWriter->writeStartElement("Lista");
        QList<account*>::iterator it;
        for(it=listona.begin(); it!=listona.end(); ++it) {
            userPremium*UP=dynamic_cast<userPremium*>(*it);
            if(UP) {
                xmlUserWriter->writeStartElement("Account");
                xmlUserWriter->writeTextElement("Username", UP->getUsername());
                xmlUserWriter->writeTextElement("Password", UP->getPassword());
                xmlUserWriter->writeTextElement("Nome", UP->getNome());
                xmlUserWriter->writeTextElement("Cognome", UP->getCognome());
                xmlUserWriter->writeTextElement("Sesso", QString::number(UP->getSesso()));
                xmlUserWriter->writeTextElement("Giorno", QString::number(UP->getData().day()));
                xmlUserWriter->writeTextElement("Mese", QString::number(UP->getData().month()));
                xmlUserWriter->writeTextElement("Anno", QString::number(UP->getData().year()));
                xmlUserWriter->writeTextElement("Tessera", UP->getTessera());
                xmlUserWriter->writeTextElement("Credito", QString::number(UP->getCredito()));
                xmlUserWriter->writeTextElement("Punti", QString::number(UP->getPunti()));
                admin* ad=dynamic_cast<admin*>(*it);
                if(ad)
                    xmlUserWriter->writeTextElement("Tipo", "AccountAdmin");
                else
                    xmlUserWriter->writeTextElement("Tipo", "AccountPremium");
                xmlUserWriter->writeEndElement();
            }
            else {
                userBase* UB=dynamic_cast<userBase*>(*it);
                if(UB) {
                    xmlUserWriter->writeStartElement("Account");
                    xmlUserWriter->writeTextElement("Username", UB->getUsername());
                    xmlUserWriter->writeTextElement("Password", UB->getPassword());
                    xmlUserWriter->writeTextElement("Nome", UB->getNome());
                    xmlUserWriter->writeTextElement("Cognome", UB->getCognome());
                    xmlUserWriter->writeTextElement("Sesso", QString::number(UB->getSesso()));
                    xmlUserWriter->writeTextElement("Giorno", QString::number(UB->getData().day()));
                    xmlUserWriter->writeTextElement("Mese", QString::number(UB->getData().month()));
                    xmlUserWriter->writeTextElement("Anno", QString::number(UB->getData().year()));
                    xmlUserWriter->writeTextElement("Tipo", "AccountBase");
                    xmlUserWriter->writeEndElement();
                }
            }
        }
        //end document
        xmlUserWriter->writeEndDocument();
        userFile->close();
    }
    delete userFile;
}

void listaAccount::loadAccount() {
    xmlUserReader = new QXmlStreamReader();
    QString filePath("../ProgettissimoP2/savedData/utenti.xml");
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
        admin* p=new admin("admin", "admin", "Admin", "Admin", QDate::currentDate(),1, "10100000", 0,0);
        listona.push_back(p);
        this->saveAccount();
    }
    else {
        xmlUserReader->setDevice(file);
        xmlUserReader->readNext();
        QString user, pass,nome, cog, tess, tipo;
        int g,m,a, punt;
        float cred;
        bool ses=false;
        bool x=false;
        while(!xmlUserReader->atEnd()) { //leggi fino alla fine del documento
            if(xmlUserReader->isStartElement()) {
                if(xmlUserReader->name() == "Lista") {
                    xmlUserReader->readNext();
                }
                if(xmlUserReader->name() == "Account") {
                    xmlUserReader->readNext();
                }
                if(xmlUserReader->name() == "Username") { user = xmlUserReader->readElementText();}
                if(xmlUserReader->name() == "Password") { pass= xmlUserReader->readElementText();}
                if(xmlUserReader->name() == "Nome") { nome = xmlUserReader->readElementText();}
                if(xmlUserReader->name() == "Cognome") { cog = xmlUserReader->readElementText();}
                if(xmlUserReader->name() == "Sesso") {
                    if ("1"==xmlUserReader->readElementText())
                        ses=true;
                    else
                        ses=false;
                }
                if(xmlUserReader->name() == "Giorno") { g=xmlUserReader->readElementText().toInt();}
                if(xmlUserReader->name() == "Mese") { m=xmlUserReader->readElementText().toInt();}
                if(xmlUserReader->name() == "Anno") { a=xmlUserReader->readElementText().toInt();}
                if(xmlUserReader->name() == "Tessera") { tess=xmlUserReader->readElementText();}
                if(xmlUserReader->name() == "Credito") { cred=xmlUserReader->readElementText().toFloat();}
                if(xmlUserReader->name() == "Punti") { punt=xmlUserReader->readElementText().toInt();}
                if(xmlUserReader->name() == "Tipo") {
                    tipo=xmlUserReader->readElementText();
                    x=true;
                }
                if(x) {
                    QDate d(a,m,g);
                    if(tipo=="AccountBase") {
                        userBase* nuovo = new userBase(user,pass,nome,cog,d,ses);
                        listona.push_back(nuovo);
                    }
                    else if (tipo=="AccountPremium") {
                        userPremium* nuovo = new userPremium(user, pass, nome, cog, d, ses, tess, cred, punt);
                        listona.push_back(nuovo);
                    }
                    else if(tipo=="AccountAdmin") {
                        admin* nuovo = new admin(user, pass, nome, cog, d, ses, tess, cred, punt);
                        listona.push_back(nuovo);
                    }
                    x=false;
                }
            }
            xmlUserReader->readNext();
        }
    }
}
