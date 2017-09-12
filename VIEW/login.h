#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QObject>
#include "ui_login.h"
#include "../MODEL/listaaccount.h"
#include "../MODEL/inventario.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(listaAccount*, QWidget *parent = 0);
    ~login();

private slots:
    void on_pushButton_clicked(); //LOGIN

    void on_pushButton_2_clicked(); //SIGN IN

private:
    listaAccount* listAcc;
    inventario* invent;
    Ui::login *ui;
};

#endif // LOGIN_H
