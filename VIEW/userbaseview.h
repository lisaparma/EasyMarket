#ifndef USERBASEVIEW_H
#define USERBASEVIEW_H

#include <QDialog>
#include "../MODEL/userBase.h"
#include "../MODEL/listaaccount.h"
#include "../MODEL/inventario.h"
#include <QTreeWidgetItem>

namespace Ui {
class UserBaseVIEW;
}

class UserBaseVIEW : public QDialog
{
    Q_OBJECT

public:
    explicit UserBaseVIEW(account*, listaAccount*, inventario*, QWidget *parent = 0);
    ~UserBaseVIEW();

private slots:
    void on_esci_clicked();

    void on_stampa_clicked();

    void on_elimina_clicked();

    void on_togli_clicked();

    void on_albero_doubleClicked();

    void on_spessa_clicked();

    void on_metti_clicked();

    void on_spessa_itemChanged();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::UserBaseVIEW *ui;
    userBase* acc;
    listaAccount* listaAc;
    inventario* invent;
    void caricaInventario() const;
    void caricaSpesa() const;
};

#endif // USERBASEVIEW_H
