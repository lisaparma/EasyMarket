#ifndef PRODOTTO_H
#define PRODOTTO_H
#include<QString>

class prodotto
{
private:
    int codice;
    QString nome;
    QString marca;
    float prezzo;
protected:
    prodotto(int, QString, QString, float);
public:
    int getCodice() const;
    QString getNome() const;
    QString getMarca() const;
    float getPrezzo() const;

    virtual float prezzoScontato() const = 0;
    virtual int getBonus() const = 0;

};

#endif // PRODOTTO_H
