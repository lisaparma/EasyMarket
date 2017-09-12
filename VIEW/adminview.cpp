#include "adminview.h"
#include "ui_adminview.h"
#include "../MODEL/admin.h"
#include <QMessageBox>
#include "../MODEL/inventario.h"
#include "VIEW/aggiungiart.h"
#include "login.h"
#include "../MODEL/alimentare.h"
#include "../MODEL/bevanda.h"
#include "../MODEL/oggettistica.h"

AdminVIEW::AdminVIEW(account* acco, listaAccount* li, inventario* in, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminVIEW),
    lista(li),
    invent(in)
{
    ad=dynamic_cast<admin*>(acco);
    ui->setupUi(this);
    caricaAccount();
    caricaInventario();
}

AdminVIEW::~AdminVIEW()
{
    delete ui;
}

// -------------------------------- GESTIONE UTENTI ---------------------------------
// per refresh dati sul QListWidget degli utenti
void AdminVIEW::caricaAccount() const {
    QList<account*>::iterator it;
    for(it=(lista->listona).begin(); it!=(lista->listona).end(); ++it) {
        if(!dynamic_cast<admin*>(*it)) {
            QString a=(*it)->getUsername();
            ui->listautenti->addItem(a);
        }
    }
    if(ui->listautenti->currentRow() == -1) {
        ui->elimina->setDisabled(1);
        ui->downgrade->setDisabled(1);
        ui->upgrade->setDisabled(1);
    }
}

// Pulsanti gestione lista
void AdminVIEW::on_elimina_clicked()
{
    QString usern=ui->listautenti->currentItem()->text();
    ad->deleteUser(lista, usern);
    lista->cleanfile(); // altrimenti sovrascrivo una cosa più corta
    lista->saveAccount();
    delete ui->listautenti->currentItem();
}
void AdminVIEW::on_upgrade_clicked()
{
    QString usern=ui->listautenti->currentItem()->text();
    ad->upgradeAccount(lista, usern);
    lista->saveAccount();
    on_listautenti_clicked(); //refresh immediato del tipo di account

}
void AdminVIEW::on_downgrade_clicked()
{
    QString usern=ui->listautenti->currentItem()->text();
    ad->downgradeAccount(lista, usern);
    lista->cleanfile(); // altrimenti sovrascrivo una cosa più corta
    lista->saveAccount();
    on_listautenti_clicked(); //refresh immediato del tipo di account
}

//INFO
void AdminVIEW::on_listautenti_clicked()
{
    QString usern=ui->listautenti->currentItem()->text();
    QList<account*>::iterator it;
    bool trovato=false;
    for(it=lista->listona.begin(); it != lista->listona.end() && !trovato; it++) {
        if((*it)->getUsername() == usern) {
            // Disattivazione pulsanti per azioni non compatibili con gli account selezionati
             userPremium* UP = dynamic_cast<userPremium*>(*it);
            if(UP) {
                ui->elimina->setDisabled(0);
                ui->upgrade->setDisabled(1);
                ui->downgrade->setDisabled(0);

                ui->username->setText(UP->getUsername());
                ui->password->setText(UP->getPassword());
                ui->nome_2->setText(UP->getNome() );
                ui->cognome->setText(UP->getCognome());
                ui->data->setText(UP->getData().toString());
                QString s;
                if(UP->getSesso()==1)
                    s="Donna";
                 else
                    s="Uomo";
                ui->sesso->setText(s);
                ui->tessera->setText(UP->getTessera());
                ui->punti->setText(QString::number(UP->getPunti()));
                ui->credito->setText(QString::number(UP->getCredito()));
            }
            else {
                userBase* UB = dynamic_cast<userBase*>(*it);
                if(UB) {
                    ui->elimina->setDisabled(0);
                    ui->upgrade->setDisabled(0);
                    ui->downgrade->setDisabled(1);

                    ui->username->setText(UB->getUsername());
                    ui->password->setText(UB->getPassword());
                    ui->nome_2->setText(UB->getNome() );
                    ui->cognome->setText(UB->getCognome());
                    ui->data->setText(UB->getData().toString());
                    QString s;
                    if(UB->getSesso()==1)
                        s="Donna";
                    else
                        s="Uomo";
                    ui->sesso->setText(s);
                    ui->tessera->setText("Non disponibile");
                    ui->punti->setText("Non disponibile");
                    ui->credito->setText("Non disponibile");
                }
            }
        }
    }
}



// ------------------------------------- GESTIONE PRODOTTI -------------------------------------------

// per refresh dati sul QTreeWidget degli articoli
void AdminVIEW::caricaInventario() const {
    ui->listainventario->clear();
    QMap<int,articolo>::iterator i;
    for(i=invent->listainv.begin(); i!=(invent->listainv).end(); ++i) {
        QTreeWidgetItem* foglia= new QTreeWidgetItem;
        foglia->setText(0, QString::number((*i).prod->getCodice()));
        foglia->setText(1, (*i).prod->getNome());
        if(!i->getQuantita()) {
            QColor c(255,0,0);
            foglia->setTextColor(0,c);
            foglia->setTextColor(1,c);
            foglia->setTextColor(2,c);
            foglia->setTextColor(3,c);
            foglia->setTextColor(4,c);
        }
        ui->listainventario->addTopLevelItem(foglia);
    }
    // Disattiva pulsanti per aggiungere lotti
    if(ui->listainventario->currentItem()==0) {
        ui->quantita->setDisabled(1);
        ui->ordina->setDisabled(1);
        ui->eliminaart->setDisabled(1);
    }
}

// Pulsanti gestione lista
void AdminVIEW::on_aggiungiart_clicked()
{
    aggiungiArt aA(invent);
    aA.exec();
    if(aA.close())
        caricaInventario();

}
void AdminVIEW::on_eliminaart_clicked()
{
    int cod=ui->listainventario->currentItem()->text(0).toInt();
    invent->listainv.remove(cod);
    invent->cleanfile();
    invent->saveArt();
    caricaInventario();
}

// Inserire più lotti
void AdminVIEW::on_ordina_clicked()
{
    int cod=ui->listainventario->currentItem()->text(0).toInt();
    invent->listainv[cod].setQuantita(invent->listainv[cod].getQuantita() + ui->quantita->value());
    invent->saveArt();
    on_listainventario_clicked();
    caricaInventario();
}

// INFO
void AdminVIEW::on_listainventario_clicked()
{
    int cod=ui->listainventario->currentItem()->text(0).toInt();
    QString tipologia;
    if(dynamic_cast<alimentare*>(invent->listainv.value(cod).prod))
        tipologia="Alimentare";
    if(dynamic_cast<bevanda*>(invent->listainv.value(cod).prod))
        tipologia="Bevanda";
    if(dynamic_cast<oggettistica*>(invent->listainv.value(cod).prod))
        tipologia="Oggettistica";
    ui->tipo->setText(tipologia);
    ui->nome->setText(invent->listainv.value(cod).prod->getNome());
    ui->marca->setText(invent->listainv.value(cod).prod->getMarca());
    ui->codice->setText(QString::number(invent->listainv.value(cod).prod->getCodice()));
    ui->prezzo->setText(QString::fromUtf8("€ ")+QString::number(invent->listainv.value(cod).prod->getPrezzo()));
    ui->disp->setText(QString::number(invent->listainv.value(cod).getQuantita())+" pz.");

    ui->quantita->setDisabled(0);
    ui->ordina->setDisabled(0);
    ui->eliminaart->setDisabled(0);
}

// ESCI
void AdminVIEW::on_pushButton_clicked()
{
    login l(lista);
    this->reject();
    l.exec();
}

// Cambio i valori dei campi dati statici delle sottoclassi di prodotto
void AdminVIEW::on_cambia_clicked()
{
    alimentare::sconto=ui->SA->text().toInt();
    alimentare::bonus=ui->BA->text().toInt();
    bevanda::sconto=ui->SB->text().toInt();
    bevanda::bonus=ui->BB->text().toInt();
    oggettistica::sconto=ui->SO->text().toInt();
    oggettistica::bonus=ui->BO->text().toInt();
}
