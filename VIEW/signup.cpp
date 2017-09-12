#include "signup.h"
#include "ui_signup.h"
#include "../MODEL/userPremium.h"
#include <QMessageBox>



SignUp::SignUp(listaAccount* listissima, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp),
    lista(listissima)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_registrati_clicked()
{
    if(ui->privacy->isChecked()) {

        // controllo username unico
        bool trovato=false;
        QList<account*>::iterator it;
        for(it=lista->listona.begin(); it != lista->listona.end() && !trovato; it++) {
            if((*it)->getUsername() == ui->username->text()) {
                trovato=true;
                QMessageBox q;
                q.setText("Username già in uso, scegline un altro");
                q.exec();
            }
        }
        if(!trovato) {
            if(ui->gold->isChecked()) {
                userPremium* nuovo = new userPremium(ui->username->text(),
                                               ui->password->text(),
                                               ui->nome->text(),
                                               ui->cognome->text(),
                                               ui->nascita->date(),
                                               ui->fem->isChecked());
                lista->listona.push_back(nuovo);
                lista->saveAccount();
                this->reject();
            }
            else {
                userBase* nuovo = new userBase(ui->username->text(),
                                               ui->password->text(),
                                               ui->nome->text(),
                                               ui->cognome->text(),
                                               ui->nascita->date(),
                                               ui->fem->isChecked());
                lista->listona.push_back(nuovo);
                lista->saveAccount();
                this->reject();
            }
        }
   }
    else {
        QMessageBox q;
        q.setText("Accettare le condizioni sulla privacy per continuare");
        q.exec();
    }
}
