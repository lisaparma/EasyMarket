#include "userbaseview.h"
#include "ui_userbaseview.h"
#include "login.h"
#include <QMessageBox>
#include <QDesktopServices>
#include "../MODEL/userPremium.h"

UserBaseVIEW::UserBaseVIEW(account* acco, listaAccount* la,inventario*i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserBaseVIEW),
    listaAc(la),
    invent(i)
{
    ui->setupUi(this);
    acc=dynamic_cast<userBase*>(acco);
    if(acc) {
        ui->nome->setText(acc->getNome());
        ui->cognome->setText(acc->getCognome());
        ui->data->setText(acc->getData().toString());
        if(acc->getSesso()) {
            ui->sesso->setText("Donna");
            ui->user->setText("Benvenuta "+acc->getUsername());
        }
        else {
            ui->sesso->setText("Uomo");
            ui->user->setText("Benvenuto "+acc->getUsername());
        }
    }
    caricaInventario();
    ui->elimina->setDisabled(1);
    ui->togli->setDisabled(1);
    ui->metti->setDisabled(1);
}

UserBaseVIEW::~UserBaseVIEW()
{
    delete ui;
}

// Riempie il QTreeWidget con gli articoli presenti in magazzino
void UserBaseVIEW::caricaInventario() const {
    ui->albero->clear();
    QMap<int,articolo>::iterator i;
    for(i=invent->listainv.begin(); i!=(invent->listainv).end(); ++i) {
        QTreeWidgetItem* foglia= new QTreeWidgetItem;
        foglia->setText(0, QString::number((*i).prod->getCodice()));
        foglia->setText(1, (*i).prod->getNome());
        foglia->setText(2, (*i).prod->getMarca());
        foglia->setText(3, QString::fromUtf8("€ ")+QString::number((*i).prod->getPrezzo()));
        foglia->setText(4, QString::number((*i).getQuantita())+" pz.");
        if(!i->getQuantita()) {
            QColor c(255,0,0);
            foglia->setTextColor(0,c);
            foglia->setTextColor(1,c);
            foglia->setTextColor(2,c);
            foglia->setTextColor(3,c);
            foglia->setTextColor(4,c);
        }
        ui->albero->addTopLevelItem(foglia);
    }
}

// Aggiungo l'elemento selezionato nella lista della spesa
void UserBaseVIEW::on_albero_doubleClicked()
{
    int k=ui->albero->currentItem()->text(0).toInt();
    if(invent->listainv[k].getQuantita() > 0) {
        bool trovato=false;
        QList<articolo>::iterator i;
        for(i=acc->spesa.begin(); i!=(acc->spesa).end() && !trovato; ++i) {
            if(i->prod->getCodice()==k){
                i->setQuantita(i->getQuantita()+1);
                trovato=true;
            }
        }
        if(!trovato) {
            articolo art(invent->listainv[k].prod, 1);
            acc->spesa.push_back(art);
        }
        invent->listainv[k].setQuantita(invent->listainv[k].getQuantita() -1);
        caricaInventario();
        caricaSpesa();
    }
    else {
        QMessageBox q;
        q.setText("Abbiamo finito la disponibilità per questo prodotto");
        q.setInformativeText("Selezioni una quantità minore o cambi articolo");
        q.exec();
    }
}

// Riempio il secondo QTreeWidget con la lista della spesa
void UserBaseVIEW::caricaSpesa() const {
    ui->spessa->clear();
    QList<articolo>::iterator i;
    for(i=acc->spesa.begin(); i!=(acc->spesa).end(); ++i) {
        QTreeWidgetItem* foglia= new QTreeWidgetItem;
        foglia->setText(0, QString::number(i->getQuantita()));
        foglia->setText(1, (*i).prod->getNome());
        ui->spessa->addTopLevelItem(foglia);
    }
    ui->money->setText(QString::fromUtf8("€ ")+QString::number(acc->soldiSpesa()));
    ui->elimina->setDisabled(1);
    ui->togli->setDisabled(1);
    ui->metti->setDisabled(1);
}

// Elimino un elemento della lista
void UserBaseVIEW::on_elimina_clicked()
{
    QString art = ui->spessa->currentItem()->text(1);
    QList<articolo>::iterator i;
    bool trovato=false;
    for(i=acc->spesa.begin(); i!=(acc->spesa).end() && !trovato; ++i) {
        if(i->prod->getNome()== art) {
            int cod=i->prod->getCodice();
            invent->listainv[cod].setQuantita(invent->listainv[cod].getQuantita() + i->getQuantita());
            caricaInventario();
            acc->spesa.erase(i);
            --i;
            caricaSpesa();
            trovato=true;
        }
    }
}

// + / -  ricorrenza di un prodotto sulla lista
void UserBaseVIEW::on_togli_clicked()
{
    QString art = ui->spessa->currentItem()->text(1);
    QList<articolo>::iterator i;
    bool trovato=false;
    for(i=acc->spesa.begin(); i!=(acc->spesa).end() && !trovato; ++i) {
        if(i->prod->getNome()== art) {
            trovato=true;
            int cod=i->prod->getCodice();
            invent->listainv[cod].setQuantita(invent->listainv[cod].getQuantita() +1);
            caricaInventario();
            if(!i->getQuantita()){
                acc->spesa.erase(i);
                i--;
                caricaSpesa();
            }
            else {
                i->setQuantita(i->getQuantita() -1);
                int qt = (ui->spessa->currentItem()->text(0).toInt())-1;
                ui->spessa->currentItem()->setText(0,QString::number(qt));
            }
        }
    }
}
void UserBaseVIEW::on_metti_clicked()
{
    QString art = ui->spessa->currentItem()->text(1);
    QList<articolo>::iterator i;
    bool trovato=false;
    for(i=acc->spesa.begin(); i!=(acc->spesa).end() && !trovato; ++i) {
        if(i->prod->getNome()== art) {
            trovato=true;
            int cod=i->prod->getCodice();
            if(invent->listainv[cod].getQuantita()) {
                invent->listainv[cod].setQuantita(invent->listainv[cod].getQuantita() -1);
                caricaInventario();
                i->setQuantita(i->getQuantita() +1);
                int qt = (ui->spessa->currentItem()->text(0).toInt())+1;
                ui->spessa->currentItem()->setText(0,QString::number(qt));
            }
        }
    }
}

// ESCI dalla view dell'account e ritorna alla login
void UserBaseVIEW::on_esci_clicked()
{
    login l(listaAc);
    this->reject();
    l.exec();
}

// ------------------------------- WIDGET SOLO BASE ----------------------------------

// Stampa lista della spesa
void UserBaseVIEW::on_stampa_clicked()
{
    QString filename = ("../ProgettissimoP2/savedData/"+acc->getNome()+acc->getCognome()+"Spesa.txt");
    QFile file(filename);
    file.remove();
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "Lista della spesa di "<<acc->getNome()<<" "<<acc->getCognome() << endl;
        stream<<"Username: "<<acc->getUsername()<<endl<<endl;
        stream<<"------------------------------"<<endl;
        QList<articolo>::iterator i;
        for(i=acc->spesa.begin(); i!=(acc->spesa).end(); ++i) {
            stream <<i->getQuantita() <<" x " <<i->prod->getNome()<<endl;
        }
        stream<<"------------------------------"<<endl;
        stream <<endl<<"Totale: "<<acc->soldiSpesa()<<" euro"<<endl;
        stream<<"------------------------------"<<endl;
        QFileInfo a(file);
        QDesktopServices::openUrl(QUrl("file:///"+a.absoluteFilePath()));
    }
}

void UserBaseVIEW::on_spessa_clicked()
{
    ui->elimina->setDisabled(0);
    ui->togli->setDisabled(0);
    ui->metti->setDisabled(0);
}

void UserBaseVIEW::on_spessa_itemChanged()
{
    ui->money->setText(QString::fromUtf8("€ ")+QString::number(acc->soldiSpesa()));
}

void UserBaseVIEW::on_checkBox_stateChanged(int arg1)
{
    if(!arg1) {
        ui->uno->hide();
        ui->due->hide();
        ui->tre->hide();
        ui->quattro->hide();
    }
    else {
        ui->uno->show();
        ui->due->show();
        ui->tre->show();
        ui->quattro->show();

    }
}

void UserBaseVIEW::on_pushButton_clicked()
{
    QList<account*>::iterator it;
    bool trovato=false;
    for(it=listaAc->listona.begin(); it != listaAc->listona.end() && !trovato; it++) {
        if(*it == acc) {
           userPremium* UP = new userPremium(acc->getUsername(),
                                             acc->getPassword(),
                                             acc->getNome(),
                                             acc->getCognome(),
                                             acc->getData(),
                                             acc->getSesso());
           listaAc->listona.erase(it);
           listaAc->listona.push_back(UP);
           listaAc->saveAccount();
           QMessageBox q;
           q.setText("Congratulazioni! Ora sei un utente PREMIUM!");
           q.setInformativeText("Rieffettua l'accesso con le tue credenziali per usufruire di tutti i benefici premium.");
           q.exec();
           trovato=true;
        }
    }
    login l(listaAc);
    this->reject();
    l.exec();
}
