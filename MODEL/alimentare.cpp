#include "alimentare.h"

alimentare::alimentare(int c, QString n, QString m, float p): prodotto(c,n,m,p) {}

float alimentare::prezzoScontato() const{
    float x, y;
    x = getPrezzo()-((getPrezzo()/100)*sconto);
    y = (float)(int)(x*100)/100;
    return y;
}

int alimentare::getBonus() const{
    return bonus;
}

int alimentare::sconto = 5;
int alimentare::bonus = 1;
