#ifndef OGGETTISTICA_H
#define OGGETTISTICA_H

#include "prodotto.h"

class oggettistica: public prodotto
{
public:
    static int bonus;
    static int sconto;

    oggettistica(int, QString, QString, float);

    float prezzoScontato() const;
    int getBonus() const;
};
#endif // OGGETTISTICA_H
