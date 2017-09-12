#include "userpremiumview.h"
#include "ui_userpremiumview.h"
#include "login.h"
#include <QMessageBox>
#include <QDesktopServices>

UserPremiumVIEW::UserPremiumVIEW(account* acco, listaAccount*la, inventario* i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPremiumVIEW),
    listaAc(la),
    invent(i)
{
    ui->setupUi(this);
    acc=dynamic_cast<userPremium*>(acco);
    if(acc) {
        ui->nome_2->setText(acc->getNome());
        ui->cognome_2->setText(acc->getCognome());
        ui->data_2->setText(acc->getData().toString());
        if(acc->getSesso()) {
            ui->sesso_2->setText("Donna");
            ui->user_2->setText("Benvenuta "+acc->getUsername());
        }
        else {
            ui->sesso_2->setText("Uomo");
            ui->user_2->setText("Benvenuto "+acc->getUsername());
        }
        ui->tessera->setText(acc->getTessera());
        ui->punti->setText(QString::number(acc->getPunti()));
        ui->credito->setText(QString::fromUtf8("€ ")+QString::number(acc->getCredito()));
    }
    caricaInventario();
    ui->elimina->setDisabled(1);
    ui->togli->setDisabled(1);
    ui->metti->setDisabled(1);
}

UserPremiumVIEW::~UserPremiumVIEW()
{
    delete ui;
}

// Riempie il QTreeWidget con gli articoli presenti in magazzino
void UserPremiumVIEW::caricaInventario() const {
    ui->albero->clear();
    bool A = ui->alim->isChecked();
    bool B = ui->bev->isChecked();
    bool O = ui->ogg->isChecked();
    QMap<int,articolo>::iterator i;
    for(i=invent->listainv.begin(); i!=(invent->listainv).end(); ++i) {
        alimentare* al = dynamic_cast<alimentare*>(i->prod);
        bevanda* be = dynamic_cast<bevanda*>(i->prod);
        oggettistica* og = dynamic_cast<oggettistica*>(i->prod);
        if((al && A) || (be && B) || (og && O)) {
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
}

// Aggiungo l'elemento selezionato nella lista della spesa
void UserPremiumVIEW::on_albero_doubleClicked()
{
    int k=ui->albero->currentItem()->text(0).toInt();
    if(invent->listainv[k].getQuantita() > 0) {
        bool trovato=false;
        QList<articolo>::iterator i;
        for(i=acc->spesa.begin(); i!=(acc->spesa).end() && !trovato; ++i) {
            if(i->prod->getCodice()==k){
                i->setQuantita(i->getQuantita() +1);
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

// Riempio il secondo QTreeWidget on la lista della spesa
void UserPremiumVIEW::caricaSpesa() const {
    ui->spessa->clear();
    QList<articolo>::iterator i;
    for(i=acc->spesa.begin(); i!=(acc->spesa).end(); ++i) {
        QTreeWidgetItem* foglia= new QTreeWidgetItem;
        foglia->setText(0, QString::number(i->getQuantita()));
        foglia->setText(1, (*i).prod->getNome());
        ui->spessa->addTopLevelItem(foglia);
    }
    ui->money->setText(QString::fromUtf8("€ ")+QString::number(acc->userBase::soldiSpesa()));
    ui->money_2->setText(QString::fromUtf8("€ ")+QString::number(acc->soldiSpesa()));
    ui->puntispesa->setText(QString::number( acc->puntiBonusSpesa()+static_cast<int>(acc->soldiSpesa())));
    ui->elimina->setDisabled(1);
    ui->togli->setDisabled(1);
    ui->metti->setDisabled(1);
}

// Elimino un elemento della lista
void UserPremiumVIEW::on_elimina_clicked()
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

// Tolgo solo una ricorrenza di un prodotto sulla lista
void UserPremiumVIEW::on_togli_clicked()
{
    QString art = ui->spessa->currentItem()->text(1);
    QList<articolo>::iterator i;
    bool trovato=false;
    for(i=acc->spesa.begin(); (i!=(acc->spesa).end()) & (!trovato); ++i) {
        if(i->prod->getNome()== art) {
            trovato=true;
            int cod=i->prod->getCodice();
            invent->listainv[cod].setQuantita(invent->listainv[cod].getQuantita() +1);
            caricaInventario();
            if(i->getQuantita()==1) {
                acc->spesa.erase(i);
                i--;
                caricaSpesa();
            }
            else{
                i->setQuantita(i->getQuantita() -1);
                int qt = (ui->spessa->currentItem()->text(0).toInt())-1;
                ui->spessa->currentItem()->setText(0,QString::number(qt));
            }
        }
    }
}
void UserPremiumVIEW::on_metti_clicked()
{
    QString art = ui->spessa->currentItem()->text(1);
    QList<articolo>::iterator i;
    bool trovato=false;
    for(i=acc->spesa.begin(); i!=(acc->spesa).end() && !trovato; ++i) {
        if(i->prod->getNome() == art) {
            trovato=true;
            int cod=i->prod->getCodice();
            if(invent->listainv[cod].getQuantita()) {
                invent->listainv[cod].setQuantita(invent->listainv[cod].getQuantita() -1);
                caricaInventario();
                i->setQuantita(i->getQuantita()+1);
                int qt = (ui->spessa->currentItem()->text(0).toInt())+1;
                ui->spessa->currentItem()->setText(0,QString::number(qt));
            }
        }
    }
}

// ESCI dalla view dell'account e ritorna alla login
void UserPremiumVIEW::on_esci_clicked()
{
    login l(listaAc);
    this->reject();
    l.exec();
}

// ------------------------------------- WIDGET SOLO PREMIUM -------------------------------------

void UserPremiumVIEW::on_spessa_clicked()
{
    ui->elimina->setDisabled(0);
    ui->togli->setDisabled(0);
    ui->metti->setDisabled(0);
}

void UserPremiumVIEW::on_spessa_itemChanged()
{
    ui->money->setText(QString::fromUtf8("€ ")+QString::number(acc->userBase::soldiSpesa()));
    ui->money_2->setText(QString::fromUtf8("€ ")+QString::number(acc->soldiSpesa()));
    ui->puntispesa->setText(QString::number(acc->puntiBonusSpesa()+static_cast<int>(acc->soldiSpesa())));
}

void UserPremiumVIEW::on_compra_clicked()
{
    if(acc->soldiSpesa() > acc->getCredito()) {
        QMessageBox msgBox;
        msgBox.setText(tr("Credito insufficente per procedere all'acquisto"));
        msgBox.setInformativeText("Ricaricare il proprio credito residuo o togliere dei prodotti dal proprio carrello");
        msgBox.exec();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText(tr("Vuoi procedere all'acquisto?"));
        msgBox.setInformativeText("Verranno detratti dal tuo credito residuo "+QString::fromUtf8("€ ")+QString::number(acc->soldiSpesa()));
        QAbstractButton* pButtonYes = msgBox.addButton(tr("Si e voglio lo scontrino"), QMessageBox::YesRole);
        msgBox.addButton(tr("Annulla"), QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {

            //stampa scontrino
            QString filename = ("../ProgettissimoP2/savedData/"+acc->getNome()+acc->getCognome()+"Scontrino.txt");
            QFile file(filename);
            file.remove();
            if (file.open(QIODevice::ReadWrite)) {
                QTextStream stream(&file);
                stream << "Spesa di "<<acc->getNome()<<" "<<acc->getCognome() << endl;
                stream<<"Username: "<<acc->getUsername()<<endl;
                stream<<"Tessera nr: "<<acc->getTessera()<<endl;
                stream<<"Credito ad inizio trassazione: "<<acc->getCredito()<<endl;
                stream<<"Punti ad inizio trassazione: "<<acc->getPunti()<<endl;

                //cambio dati
                acc->setPunti(acc->getPunti() + (ui->puntispesa->text().toInt()));
                acc->setCredito( acc->getCredito() - (acc->soldiSpesa()));
                ui->punti->setText(QString::number(acc->getPunti()));
                ui->credito->setText(QString::fromUtf8("€ ")+QString::number(acc->getCredito()));
                invent->saveArt();
                listaAc->saveAccount();
                //

                stream<<"-----------------------------------"<<endl;
                QList<articolo>::iterator i;
                for(i=acc->spesa.begin(); i!=(acc->spesa).end(); ++i) {
                    stream <<i->getQuantita() <<" x " <<i->prod->getNome()<<endl;
                }
                stream<<"-----------------------------------"<<endl;
                stream<<endl<<"Totale: "<<acc->soldiSpesa()<<" euro"<<endl;
                stream<<"Punti: "<<(acc->puntiBonusSpesa()+static_cast<int>(acc->soldiSpesa()))<<endl;
                stream<<"-----------------------------------"<<endl;
                stream<<"Credito dopo la transazione: "<<acc->getCredito()<<" euro"<<endl;
                stream<<"Punti totali: "<<acc->getPunti()<<endl;
                stream<<"-----------------------------------"<<endl;
                QFileInfo a(file);
                QDesktopServices::openUrl(QUrl("file:///"+a.absoluteFilePath()));
            }
            ui->money->setText(QString::fromUtf8("€ ")+"0");
            ui->money_2->setText(QString::fromUtf8("€ ")+"0");
            ui->puntispesa->setText("0");
            acc->spesa.clear();
            ui->spessa->clear();
        }
    }
}

void UserPremiumVIEW::on_checkBox_stateChanged(int arg1)
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

void UserPremiumVIEW::on_ricarica_clicked()
{
    acc->setCredito(acc->getCredito() + ui->spinBox->value());
    ui->credito->setText(QString::fromUtf8("€ ")+QString::number(acc->getCredito()));
    listaAc->saveAccount();

}

void UserPremiumVIEW::on_alim_stateChanged()
{
    caricaInventario();
}

void UserPremiumVIEW::on_bev_stateChanged()
{
    caricaInventario();
}

void UserPremiumVIEW::on_ogg_stateChanged()
{
    caricaInventario();
}
