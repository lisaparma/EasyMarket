#include "prodotto.h"

prodotto::prodotto(int cod, QString n, QString m, float p):
    codice(cod),
    nome(n),
    marca(m),
    prezzo(p)
{}

int prodotto::getCodice() const {return codice;}
QString prodotto::getNome() const {return nome;}
QString prodotto::getMarca() const {return marca;}
float prodotto::getPrezzo() const {return prezzo;}
