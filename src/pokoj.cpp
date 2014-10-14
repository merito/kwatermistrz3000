#include "pokoj.h"

Pokoj::Pokoj(){
    this->zajetychMiejsc=0;
}

void Pokoj::setPokoj(int numer, int liczbaMiejsc)
{
    this->numer=numer;
    this->liczbaMiejsc=liczbaMiejsc;
    this->osoby=new Osoba[liczbaMiejsc];
}

Osoba* Pokoj::getOsobyZPokoju(){
    return this->osoby;
}

Osoba* Pokoj::getOsobaZPokoju(int indeks){
    return (this->osoby)+indeks;
}

int Pokoj::getNumerPokoju(){
    return this->numer;
}

int Pokoj::getLiczbaMiejsc(){
    return this->liczbaMiejsc;
}

int Pokoj::getLiczbaZajetychMiejsc(){
    int wynik=0;
    for(int i=0;i<liczbaMiejsc;i++){
        if(osoby[i].getStan()){
            wynik++;
        }
    }
    return wynik;
}
