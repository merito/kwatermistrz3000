#ifndef POKOJ_H
#define POKOJ_H

#include "osoba.h"

class Pokoj
{
public:
    Pokoj();
    void setPokoj(int numer, int liczbaMiejsc);
    Osoba* getOsobyZPokoju();
    Osoba* getOsobaZPokoju(int);
    int getNumerPokoju();
    int getLiczbaMiejsc();
    int getLiczbaZajetychMiejsc();
    Osoba *osoby;
private:
    int numer;
    int liczbaMiejsc;
    int zajetychMiejsc; 
};

#endif // POKOJ_H
