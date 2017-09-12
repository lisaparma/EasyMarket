#include "articolo.h"

articolo::articolo(prodotto* p, int quant):
    quantita(quant),
    prod(p)
{}

int articolo::getQuantita() const {
    return quantita;
}
void articolo::setQuantita(int x) {
    quantita=x;
}
