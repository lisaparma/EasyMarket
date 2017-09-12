#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include <QDialog>
#include "../MODEL/admin.h"
#include "../MODEL/listaaccount.h"
#include "../MODEL/inventario.h"

namespace Ui {
class AdminVIEW;
}

class AdminVIEW : public QDialog
{
    Q_OBJECT

public:
    explicit AdminVIEW(account*, listaAccount*, inventario*, QWidget *parent = 0);
    ~AdminVIEW();
    void caricaAccount() const;
    void caricaInventario() const;
    Ui::AdminVIEW *ui;

private slots:
    // ------ ACCOUNT ------
    void on_elimina_clicked();
    void on_upgrade_clicked();
    void on_downgrade_clicked();
    void on_listautenti_clicked();

    // ----- ARTICOLI -----
    void on_aggiungiart_clicked();
    void on_eliminaart_clicked();
    void on_ordina_clicked();
    void on_listainventario_clicked();

    void on_pushButton_clicked();

    void on_cambia_clicked();

private:
    admin* ad;
    listaAccount* lista;
    inventario* invent;
};

#endif // ADMINVIEW_H
