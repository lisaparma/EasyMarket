#ifndef ALIMENTARE_H
#define ALIMENTARE_H

#include "prodotto.h"

class alimentare: public prodotto
{
public:
    alimentare(int, QString, QString, float);

    static int bonus;
    static int sconto;

    float prezzoScontato() const;
    int getBonus() const;
};

#endif // ALIMENTARE_H
