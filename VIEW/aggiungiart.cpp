#include "aggiungiart.h"
#include "ui_aggiungiart.h"
#include "../MODEL/articolo.h"
#include "adminview.h"
#include "../MODEL/alimentare.h"
#include "../MODEL/bevanda.h"
#include "../MODEL/oggettistica.h"
#include <QMessageBox>

aggiungiArt::aggiungiArt(inventario* inv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aggiungiArt),
    i(inv)
{
    ui->setupUi(this);
}

aggiungiArt::~aggiungiArt()
{
    delete ui;
}



void aggiungiArt::on_aggiungi_clicked()
{
    if(!ui->prezzo->text().toFloat()) {
        QMessageBox q;
        q.setIcon(QMessageBox::Warning);
        q.setText("Inserisci un prezzo valido.");
        q.setInformativeText("Deve essere un numero > 0, nel formato euro.centesimi (non "","" )");
        q.exec();
    }
    else {
        int k=100;
        bool x=true;
        while(x) {
            if(i->listainv.contains(k))
                k++;
            else
                x=false;
        }
        QString nom = ui->nome->text();
        QString mar = ui->marca->text();
        float prez = ui->prezzo->text().toFloat();
        QString tipo = ui->tipo->currentText();

        if(tipo=="Alimentare"){
            alimentare* p = new alimentare(k,nom,mar,prez);
            articolo ar(p);
            i->listainv.insert(k,ar);
        }
        else if(tipo=="Bevanda") {
            bevanda* p = new bevanda(k,nom,mar,prez);
            articolo ar(p);
            i->listainv.insert(k,ar);
        }
        else if(tipo=="Oggettistica") {
            oggettistica* p=new oggettistica(k,nom,mar,prez);
            articolo ar(p);
            i->listainv.insert(k,ar);
        }
        i->saveArt();
        this->reject();
    }
}
