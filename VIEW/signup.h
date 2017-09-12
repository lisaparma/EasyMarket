#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "../MODEL/listaaccount.h"
namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(listaAccount*, QWidget *parent = 0);
    ~SignUp();

private slots:
    void on_registrati_clicked();

private:
    Ui::SignUp *ui;
    listaAccount* lista;
};

#endif // SIGNUP_H
