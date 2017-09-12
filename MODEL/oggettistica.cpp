#include "oggettistica.h"

oggettistica::oggettistica(int c, QString n, QString m, float p): prodotto(c,n,m,p) {}

float oggettistica::prezzoScontato() const{
    float x, y;
    x = getPrezzo()-((getPrezzo()/100)*sconto);
    y = (float)(int)(x*100)/100;
    return y;
}

int oggettistica::getBonus() const{
    return bonus;
}

int oggettistica::sconto = 0;
int oggettistica::bonus = 0;
