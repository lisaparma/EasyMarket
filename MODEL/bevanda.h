#ifndef BEVANDA_H
#define BEVANDA_H

#include "prodotto.h"

class bevanda: public prodotto
{
public:
    static int bonus;
    static int sconto;
    bevanda(int, QString, QString, float);

    float prezzoScontato() const;
    int getBonus() const;
};

#endif // BEVANDA_H
