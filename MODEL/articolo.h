#ifndef ARTICOLO_H
#define ARTICOLO_H
#include "prodotto.h"

class articolo
{
private:
    int quantita;
public:
    prodotto* prod;

    articolo(prodotto* =0, int=0);

    int getQuantita() const;
    void setQuantita(int);
};

#endif // ARTICOLO_H
