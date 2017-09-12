#ifndef AGGIUNGIART_H
#define AGGIUNGIART_H

#include <QDialog>
#include"../MODEL/inventario.h"

namespace Ui {
class aggiungiArt;
}

class aggiungiArt : public QDialog
{
    Q_OBJECT

public:
    explicit aggiungiArt(inventario*,QWidget *parent = 0);
    ~aggiungiArt();

private slots:
    void on_aggiungi_clicked();

private:
    Ui::aggiungiArt *ui;
    inventario* i;
};

#endif // AGGIUNGIART_H
