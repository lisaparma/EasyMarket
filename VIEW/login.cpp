#include "login.h"
#include "ui_login.h"
#include "userpremiumview.h"
#include "adminview.h"
#include "userbaseview.h"
#include "signup.h"
#include <QMessageBox>

login::login(listaAccount* lista, QWidget *parent) :
    QDialog(parent),
    listAcc(lista),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->username->setFocus();
    invent=new inventario();
    invent->loadArt();
}

login::~login()
{
    delete ui;
}

// Cliccando su LOGIN
void login::on_pushButton_clicked()
{
    bool trovato = false;
    QList<account*>::iterator it;
    for(it=(listAcc->listona).begin(); it != (listAcc->listona).end() && !trovato; it++) { //Ciclo tutti gli account sulla lista
        if((*it)->getUsername() == ui->username->text()) {
            trovato=true; // mi fermo quando trovo un username che corrisponde
            if((*it)->getPassword()==ui->password->text()) {
                /* se username e password corrispondono ad un account
                 * controllo a che tipo appartiene quell'account ed apro la finestra
                 * corrispondente passandole un puntatore a quell'account */
                if(dynamic_cast<admin*>(*it)) {
                    QMessageBox q;
                    q.setText("Vuoi entrare come Admin o come Utente Premium?");
                    QAbstractButton* premiumbut=q.addButton("Premium", QMessageBox::YesRole);
                    QAbstractButton* adminbut=q.addButton("Admin", QMessageBox::NoRole);
                    q.exec();
                    if(q.clickedButton()==adminbut) {
                        AdminVIEW AV(*it, listAcc, invent);
                        this->reject();
                        AV.exec();
                    }
                    else {
                        if(q.clickedButton()==premiumbut) {
                            UserPremiumVIEW UPV(*it, listAcc, invent);
                            this->reject();
                            UPV.exec();
                        }
                    }
                }
                else {
                    if(dynamic_cast<userPremium*>(*it)) {
                        UserPremiumVIEW UPV(*it, listAcc, invent);
                        this->reject();
                        UPV.exec();
                    }
                    else if(dynamic_cast<userBase*>(*it)) {
                        UserBaseVIEW UBV(*it, listAcc, invent);
                        this->reject();
                        UBV.exec();
                    }
                }
            }
            else {
                QMessageBox q;
                q.setIcon(QMessageBox::Critical);
                q.setText("Password errata");
                q.exec();
            }
        }
    }
    if(trovato==false){
        QMessageBox q;
        q.setIcon(QMessageBox::Warning);
        q.setText("Nessun utente trovato con questo username");
        q.exec();
    }
}

// Cliccando su Sign In
void login::on_pushButton_2_clicked()
{
    SignUp sp(listAcc);
    sp.exec();
}
