#ifndef USERPREMIUMVIEW_H
#define USERPREMIUMVIEW_H

#include <QDialog>
#include "../MODEL/userPremium.h"
#include"../MODEL/listaaccount.h"
#include "../MODEL/inventario.h"

namespace Ui {
class UserPremiumVIEW;
}

class UserPremiumVIEW : public QDialog
{
    Q_OBJECT

public:
    explicit UserPremiumVIEW(account*, listaAccount*, inventario*, QWidget *parent = 0);
    ~UserPremiumVIEW();

private slots:
    void on_esci_clicked();

    void on_elimina_clicked();

    void on_togli_clicked();

    void on_albero_doubleClicked();

    void on_spessa_clicked();

    void on_compra_clicked();

    void on_metti_clicked();

    void on_spessa_itemChanged();

    void on_checkBox_stateChanged(int arg1);


    void on_ricarica_clicked();

    void on_alim_stateChanged();

    void on_bev_stateChanged();

    void on_ogg_stateChanged();

private:
    Ui::UserPremiumVIEW *ui;
    userPremium* acc;
    listaAccount* listaAc;
    inventario* invent;
    void caricaInventario() const;
    void caricaSpesa() const;
};

#endif // USERPREMIUMVIEW_H
