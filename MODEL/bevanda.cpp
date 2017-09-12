#include "bevanda.h"

bevanda::bevanda(int c, QString n, QString m, float p): prodotto(c,n,m,p){}

float bevanda::prezzoScontato() const{
    float x, y;
    x = getPrezzo()-((getPrezzo()/100)*sconto);
    y = (float)(int)(x*100)/100;
    return y;
}

int bevanda::getBonus() const {
    return bonus;
}

int bevanda::sconto = 10;
int bevanda::bonus = 2;
