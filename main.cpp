#include <QApplication>
#include <QWidget>

#include "MODEL/admin.h"
#include "VIEW/login.h"
#include "MODEL/listaaccount.h"
#include <QXmlStreamWriter>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    listaAccount* lis=new listaAccount;
    lis->loadAccount();

    // Lancia la finestra di login
    login l(lis);
    l.show();


    return a.exec();
}

